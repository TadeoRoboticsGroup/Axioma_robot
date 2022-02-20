# Axioma.io
Este proyecto tiene como objetivo principal la creacion de una plataforma de robotica movil autonoma con uso de herramnietas de open hardware y open source, como lo arduino, raspberry pi y el sistema operativo para robots en su versión 2 distribución Foxy o simplemente ROS2 Foxy.

![Axioma](https://github.com/MrDavidAlv/Axioma_robot/blob/main/image/axioma.jpeg)

## 1 Hardware
El hardware se encuentra compuesto por dos herramientas open hardware muy usadas en el desarrollo y prototipado rapido de dispositivos electrónicos y mecátronicos y una raspberry pi. Estos dispositivos estan clasificados ***"One Chip"*** por todo en uno solo como lo es arduino que posee un microcontrolador, chip para la comunicación serial, reguladores de voltajes y demas componentes electronicos que permitan conectar actuadores y sensores de forma facil y rapida. En la clasificación One Chip tambien tenemos lo que es la raspberry pi que lleva a bordo un chip microprocesador, ram, video, ethernet/wifi, regulador, comunicación serial que le permiten conectar otros dispositivos como camaras, monitores y toda clase de perifericos usb que le brindan a esta pequeña tarjeta la posibilidad de crear muchas aplicaciones web, IoT, Entretenimiento y Robotica.

  * ### Sensores y acturadores

  * ### [Arduino](https://www.arduino.cc/)

  * ### [Raspberry pi](https://www.raspberrypi.com/)



## 2 Software
### 2.1 [ROS/ROS2](https://www.ros.org/)
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
* #### Temas
* #### Acciones
* #### Servicios
* #### Parametros
* #### Lanzaderas
* #### Urdf

### 2.2 [Gazebo](http://gazebosim.org/)
