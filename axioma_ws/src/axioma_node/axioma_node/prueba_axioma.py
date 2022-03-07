import time
import serial
#ffind serial port C:\Users\olmer\anaconda3\python -m serial.tools.list_ports

#print(serial.tools.list_ports)

ser = serial.Serial(timeout=0.1,write_timeout=0.01)
ser.baudrate = 115200
ser.port = '/dev/ttyACM0'
ser.open()
time.sleep(1)
if ser.isOpen():

    v_r=255
    v_l=100
    command=1
    for i in range(0,200):
        v_l+=1
        if v_l==255:
            v_l=100
        #protocolo de envio de datos
        comandos='z='+str(command)+' vl='+str(v_l)+' vr='+str(v_r)+'\n'
        #print(comandos)
        ser.write(comandos.encode())
        #lectura de los datos
        line=ser.read_until().decode("utf-8")
        if len(line)>0:
            datos=line[:-2].split(',')
            if len(datos)==3:
                print(i,datos)
            else:
                print("error de recepcion de datos")    
        else:
            print(i)
        time.sleep(0.1)

    comandos='z='+str(1)+' vl='+str(0)+' vr='+str(0)+'\n'
    ser.write(comandos.encode())
    ser.close()
else:
    print("error")
