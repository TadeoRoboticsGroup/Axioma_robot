# Axioma.io   :hugs: :muscle: :seedling: :nerd_face:

Este proyecto de grado aborda el desarrollo de software con el sistema operativo de robots ROS2 para convertir la plataforma robótica móvil Axioma.io desarrollado por estudiantes del semillero de robótica SIRO en una plataforma autónoma con la capacidad de percibir y entender el entorno de trabajo en el que se encuentre y pueda calcular una ruta para desplazarse de un punto de origen a un punto final llevando a bordo algún producto, todo esto sin intervención de un operario y sirviendo así como una solución a la automatización de la logística en cadenas y/o procesos de producción cumpliendo los requerimientos de la industria en el suministro, planificación , gestión y control del almacenamiento de mercancía para conseguir los niveles más altos de servicio, calidad y eficiencia al menor tiempo y costo posible. 

#### palabras clave

Robot móvil, autónomo, logística, planeación, trayectorias. 

#### Objetivo general

*Diseñar, simular e implementar software de planificación de trayectorias robóticas para la plataforma de robótica móvil Axioma.io con el fin de cumplir con la función de transportar productos de forma autónoma desde un punto inicial a un punto final dentro de un espacio de trabajo determinado, garantizando la automatización de la logística en la gestión y coordinación de estas actividades dentro de una cadena o proceso de producción.*

##### Objetivos específicos

* Diseñar un entorno de trabajo tridimensional que simula el área de trabajo con obstáculos.  
* Instrumentar el robot virtual con los sensores encargados de orientación, posición, navegación y mapeo.
* Programar el ecosistema de ROS con todos paquetes de los nodos necesarios para la localización, control y navegación, así como también el mapeo del entorno de trabajo del robot. 
* Desarrollar las técnicas de planeación de trayectorias robóticas que indique el camino para que el robot pueda ir de un punto a otro. 
* Integrar el software desarrollado para la localización, control, navegación, mapeo y planificación de trayectorias  en el robot físico Axioma.io. 
Agregar sensores para realizar odometría y cálculo de velocidad de giros del robot.  

![Axioma](https://github.com/MrDavidAlv/Axioma_robot/blob/main/image/axioma.jpeg)

![open_source](https://github.com/MrDavidAlv/Axioma_robot/blob/main/image/open_software.jpeg)

## 1 Hardware
El hardware se encuentra compuesto por dos herramientas open hardware muy usadas en el desarrollo y prototipado rapido de dispositivos electrónicos y mecátronicos y una raspberry pi. Estos dispositivos estan clasificados ***"One Chip"*** por todo en uno solo como lo es arduino que posee un microcontrolador, chip para la comunicación serial, reguladores de voltajes y demas componentes electronicos que permitan conectar actuadores y sensores de forma facil y rapida. En la clasificación One Chip tambien tenemos lo que es la raspberry pi que lleva a bordo un chip microprocesador, ram, video, ethernet/wifi, regulador, comunicación serial que le permiten conectar otros dispositivos como camaras, monitores y toda clase de perifericos usb que le brindan a esta pequeña tarjeta la posibilidad de crear muchas aplicaciones web, IoT, Entretenimiento y Robotica.

  * ### Sensores y acturadores
    * Lidar
    * Camera
    * Encoders
    * Motor DC
  * ### Fuente de alimentación
  * ### Micros
    * ### [Arduino](https://www.arduino.cc/)

    ![arduino](https://github.com/MrDavidAlv/Axioma_robot/blob/main/image/arduino.jpeg)

    * ### [Raspberry pi](https://www.raspberrypi.com/)

    ![raspberry](https://github.com/MrDavidAlv/Axioma_robot/blob/main/image/raspberry.jpeg)


## 2 Software

### 2.1 [ROS/ROS2](https://www.ros.org/)  

![ros](https://github.com/MrDavidAlv/Axioma_robot/blob/main/image/ros.jpeg)
[source](https://github.com/ros)

![service](https://github.com/MrDavidAlv/Axioma_robot/blob/main/image/service.gif)

### [ROS2 Foxy](https://docs.ros.org/en/foxy/index.html)
  * #### [Librerias](http://wiki.ros.org/Client%20Libraries)
  Son las herramientas que permiten la interación entre ROS y el codigo fuente del proyecto construido en determinado lenguaje. Las librerias principales son RCLCPP para C++ y RCLPY para Python, pero hay librerias clientes para todos los gustos y necesidades. 
  
   * ###### [rclcpp](https://docs.ros2.org/foxy/api/rclcpp/index.html) 
   Es la biblioteca cliente de ROS proporciona la API canónica de ***C++*** para interactuar con ROS.
    
   * ###### [rclpy](https://docs.ros2.org/latest/api/rclpy/index.html) 
   Es la biblioteca cliente de ROS proporciona la API canónica de ***Python*** para interactuar con ROS.
    
   Acontinuación veremos otros ejemplos de las librerias clientes para ROS.
   
|    Libreria   | Lenguaje    |   Libreria       | Lenguaje     |
| ------------- | ----------- | ---------------- | ------------ |
| ***roscs***   | *Mono/.NET* | ***rosnode***    | *Node.js*    |
| ***rosseus*** | *Lisp*      | ***RobotOS.jl*** | *Julia*      |
| ***rosgo***   | *Go*        | ***PhaRos***     | *Pharo*      |
| ***roshask*** | *Haskell*   | ***rosR***       | *R*          | 
| ***rosjava*** | *Java*      | ***rosRuby***    | *Ruby*       |


---

* #### Nodos

Nodos importantes usados en el proyecto axioma

|  Nodo                |descripcion |
|----------------------|------------|
| ***Axioma_urdf***    |sasdddddddddddddddddddddddddddddddddddddddddddddddddddddddd |
| ***Axioma_gazebo***  |sas |
| ***Axioma_node***    |sas |
| ***Axioma_nav2***    |sas |

---

* #### Temas

---

* #### Acciones

---

* #### Servicios

---

* #### Parametros

---

* #### Lanzaderas

---

* #### Urdf

---

* #### TF/TF2

![frames](https://github.com/MrDavidAlv/Axioma_robot/blob/main/image/frames4.png)

---

## 3 Modelado 3D

## 4 Modelo matemático 

![diff](https://github.com/MrDavidAlv/Axioma_robot/blob/main/image/diff.jpeg)


#### Odometría
* ##### Modelo matematico robot Axioma

Posición Robot

    Vx=V*cos(θ)

    Vy=V*sen(θ)


 
Ecuaciones de velocidades lineales y angulares

    vL=v-(wL/2) Velocidad derecha
   
    vR=v+(wL/2) Velocidad izquierda
   
    w=(vL-vR)/L Velocidad Angular
   
L: longitud entre las ruedas

calculo de  w

    w=90º/Δt   ->   w=(2π/ticks)/Δt  (rad/s)

Periodo T

    T=Δt

Frecuencia (f)

    f=1/T

Velocidad angular

    w=2π/T

Velocidad lineal  

    V=W*R


* ##### Odometria con encoders

- Dc(distancia central[Posición])  
- Dr(distancia derecho)  
- Dl(distancia izquierdo)

        Dc=(DR+DL)/2  

Para actualizar la posición

    x'=x+Dc*cos(θ)
    y'=y+Dc*sin(θ)
    θ'=θ+(Dr-Dl)/L

    ΔTics =ΔTick - Tick

Distancia recorrida

    D=2πR(ΔTick/N)   
    
N: numero de tiks que tiene la rueda


* ##### Feedback de Retroalimentación

Diagrama del feedback en la electrónica

       
Se debe pasar:

    Tick's ---> (x,y)
    Tick's ---> Distancia ---> (X,Y)


Tiempos de interrupción 
cada cierto tiempo ejecutar una acción de control
              
| muestre anterior | ***Δmuestreo 10ms*** |muestreo actual | 
|------------------|----------------------|----------------|
|                  | ^ ^ ^ ^ ^ ^ ^ ^ ^ ^  |                |
            
Δmuestreo = muestreoActual - muestreoAnterior

    if(Δmuestreo>10ms)  ===>  Ejecuta acción de Control
    
###  5 Simulación
#### [Gazebo](http://gazebosim.org/)
