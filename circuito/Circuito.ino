/*
 * O programa implementa el control de velocidad de los motores y un protocolo de comuniacion
 * librerias:
 * https://github.com/avandalen/avdweb_FreqPeriodCounter  mejor usar de hardware como la de teensy, pero esta solo soporta 1 contador
 * https://www.pjrc.com/teensy/td_libs_TimerOne.html   utilizada para el ciclo del PID
 * https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library driver del motor(open loop)
 * https://github.com/br3ttb/Arduino-PID-Library
 * 
 * 
 * CONCLUSION FUNCIONA SOLO HACIA DELANTE POR EL PROBLEMA DE LA DIREECIÖN DEL ENCODER CON EL PID SE CONFUNDE MUCHISIMO!!!
 * posibles soluciones:
 *   -tener un controlador hacia adelante y otro hacia atras siempre con la señal de control entre [0,max] o [0,min]
 *   -medir correctamente velocidad :)
 *   - actualmente utiliza el signo del setPoint , lo que claramente no aplica si la señal de control puede ser negativa o si presenta cambios bruscos.
 *   - El signo de la señal de control no se puede usar porque es muy nerviosa y puede estar hacia adelante cuando se envia un comando hacia atras
 */





#include <string.h>
#include <FreqPeriodCounter.h>
#include <TimerOne.h>
#include <PID_v1.h>


#define STOP_TIMEOUT 80000 //tiempo en us para detectar que el motor esta parado porque el encoder no mide 0, TODO: cual es el mejor timeout para determinar que el motor esta parado? 
#define CONTROL_TS   20000  //periodo de tiempo  en us para el control
#define BUFFER_RX    20   //tamaño del buffer de datos de entrada
#define TIMEOUT_COMM  10000 //timeout en ms por si deja de llegar comunicación el robot va a parar
  
//#define DEBUG 1

#define TBG
#ifdef TBG
#include <SparkFun_TB6612.h>
#endif

//variables rx serial
char incomingBytes[BUFFER_RX];
size_t len=0;
//variables para comuniación
int m=0,z;
int vl;
int vr;

//variable timeout
int ii=0;


//variables encoder

const byte encoder_l_pin = 18;
const byte encoder_r_pin = 19;

FreqPeriodCounter encoder_l_counter(encoder_l_pin, micros);
FreqPeriodCounter encoder_r_counter(encoder_r_pin, micros);
double speed_r=0;  //sensor
int speed_r_tx;
double motor_r_pwm=0;  //senal de control
double speed_r_set_point=0;   //setpoint
 
double speed_l=0;
int speed_l_tx;
double motor_l_pwm=0;
double speed_l_set_point=0;

//Control Motores
double Kp=0.18, Ki=1, Kd=0;
PID PID_r(&speed_r, &motor_r_pwm, &speed_r_set_point, Kp, Ki, Kd,P_ON_E, DIRECT);
PID PID_l(&speed_l, &motor_l_pwm, &speed_l_set_point, Kp, Ki, Kd,P_ON_E, DIRECT);

//Puente H y control PWM
  int  PWM_L = 4;
  int  PWM_R = 5;
  //L
  int in1=12;
  int in2=9;
  //R
  int in3=8;
  int in4=7;

#ifdef TBG
//port of the TB6612
#define AIN1 2
#define AIN2 4
#define PWMA 6
#define BIN1 8
#define BIN2 3
#define PWMB 7
#define STBY 9
Motor motor1 = Motor(AIN1, AIN2, PWMA, 1, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, 1, STBY);
#endif


void setup() {
 pinMode(12, OUTPUT);
 digitalWrite(12, LOW);
   //Puente H Motores
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(PWM_R, OUTPUT);
  PID_r.SetMode(AUTOMATIC);
  PID_r.SetOutputLimits(0,255);
  PID_l.SetMode(AUTOMATIC);
  PID_l.SetOutputLimits(0,255);
  
   Timer1.initialize(CONTROL_TS);  //control a 50hz
   Timer1.attachInterrupt(motor_control); // 
//encoder

  attachInterrupt(digitalPinToInterrupt(encoder_l_pin), encoder_l_function, CHANGE);

  attachInterrupt(digitalPinToInterrupt(encoder_r_pin), encoder_r_function, CHANGE);
 
 Serial.begin(115200);

}

void loop() {

//PROTOCOL TODO: improve add chksum
  if (Serial.available()) {
    len=Serial.readBytesUntil('\n', incomingBytes, sizeof(incomingBytes) / sizeof(char) );
    if(incomingBytes[0]=='z'){// && incomingBytes[len-1]=='1'){
      sscanf(incomingBytes,"z=%d vl=%d vr=%d",&z,&vl,&vr);
      m=z;
#ifdef DEBUG
      Serial.print(z);
      Serial.print(',');
      Serial.print(vl);
      Serial.print(',');
      Serial.println(vr);
#endif
    }
    memset( incomingBytes,0, sizeof(incomingBytes));
   }

//SENT TO PC 
  if (m==1){
    
   m=0;
   noInterrupts();
   speed_l_set_point=1.0*constrain(vl,0,255); ///TODO: por el encoder no funciona hacia atras
   speed_r_set_point=1.0*constrain(vr,0,255);
   speed_r_tx=(int)speed_r;
   speed_l_tx=(int)speed_l;
   interrupts();
   ii=0;
   Serial.print(speed_l_tx);
   Serial.print(',');
   Serial.print(speed_r_tx);
   Serial.print(',');
   Serial.print(millis());
   Serial.print("\n");
   digitalWrite(12, LOW);
    }
    else{
      if (ii>TIMEOUT_COMM){//lost connection (stop)
        //brake(motor1, motor2);
         noInterrupts();
        speed_l_set_point=0;
        speed_r_set_point=0;
        motor_l(0);
        motor_r(0);
         interrupts();
        //Serial.println("nop");
      }else{
        ii++;
        delay(1);
        }
    }
      
      
      

    
        
}

/**
 * motor izquierdo
 * speed debe venir entre [--255 y 255]
 */
void motor_l(int speed){
  #ifdef TBG
  motor2.drive(speed);
  #endif
  #ifndef TBG
  if(speed>0){
  digitalWrite (in3, HIGH);
  digitalWrite (in4, LOW);
  }else{
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);
  speed=-1*speed;
    }
    //digitalWrite (PWM_L, HIGH);
  analogWrite(PWM_L,constrain(speed, 0, 255));
  #endif
}

/**
 * motor derecho
 * speed debe venir entre [-255 y 255]
 */
void motor_r(int speed){
  #ifdef TBG
  motor1.drive(speed);
  #endif
  #ifndef TBG
  if(speed>0){
  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);
  }else{
  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
    speed=-1*speed;
    }
  analogWrite(PWM_R,constrain(speed, 0, 255));
  #endif
}
/**
 * Interrupción del pin del "encoder"
 */
void encoder_r_function(){
  encoder_r_counter.poll();
  }
  /**
   * interrupción del pin del "encoder"
   */
void encoder_l_function(){
  encoder_l_counter.poll();
  }
double mal_signo(double x){ return x < 0.0 ? -1.0 : 1.0;}//x ? 1.0 : 0.0; }
  
 /** 
  *  Función que realiza con el timerOne del arduino configurado con CONTROL_TS
  *  
  */
  void motor_control(){
    long frequency_l=0;
    long frequency_r=0;
    encoder_r_counter.poll();      
    encoder_l_counter.poll();
    
    if(encoder_l_counter.ready()){
        frequency_l=encoder_l_counter.hertz(10); //TODO: calibrar la velocidad correcta!!!!!
        if(frequency_l<500)
          speed_l=frequency_l*mal_signo(speed_l_set_point); //TODO: el signo del voltaje al motor es la mejor opción?no lo es, seria mejor del comando anterior speed_l_set_point_1
    }else if(encoder_l_counter.elapsedTime>=STOP_TIMEOUT) 
        speed_l=0;
        
    if(encoder_r_counter.ready()){
        frequency_r=encoder_r_counter.hertz(10);
        if(frequency_r<500)
          speed_r=frequency_r*mal_signo(speed_r_set_point);
    }else if(encoder_r_counter.elapsedTime>=STOP_TIMEOUT) 
        speed_r=0;
        
    //PID
    //motor_l_pwm=constrain(2*(speed_l_set_point-speed_l), -255, 255);
    //motor_r_pwm=speed_r_set_point;//constrain(2*(speed_r_set_point-speed_r), -255, 255);
    if(speed_l_set_point==0) //add deadband of motor
          motor_l(0);
    else{
        PID_l.Compute();
       motor_l((int)motor_l_pwm);  
      }  
      if(speed_r_set_point==0) //TODO: adicionar zona muerta del motor que no vale la pena usar PID y revisar en la libreria PID si es recomendado cambiarlo a modo manual/automatico para reiniciar variables internas del PID
        motor_r(0);
      else{
        PID_r.Compute();
         motor_r((int)motor_r_pwm);
      } 
    }
