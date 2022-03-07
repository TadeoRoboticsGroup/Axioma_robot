# Copyright 2021 LMA, UNICAMP
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import rclpy
from rclpy.node import Node
import time
import serial

from sensor_msgs.msg import JointState
from geometry_msgs.msg import Twist
from std_msgs.msg import Header


class AxiomaNode(Node):

    def __init__(self):
        super().__init__('axioma_node')
        self.joint_state_pub_ = self.create_publisher(JointState, 'joint_states', 10)
        self.cmd_vel_sub_ = self.create_subscription(
            Twist,
            'cmd_vel',
            self.cmd_vel_callback,
            1)

        try:
            self.ser = serial.Serial(timeout=0.045,write_timeout=0.001)
            self.ser.baudrate = 115200
            self.ser.port = '/dev/ttyACM0'
            self.ser.open()
            time.sleep(1)
            self.simulation = False
        except:
            self.simulation = True
            self.get_logger().warning('Error al abrir el puerto Serial, usando simulación cinemática')

        #TODO: adicionar parametros (configurar correctamente)
        self.t_s = 0.05  # seconds
        self.L = 0.12 # distancia entre las ruedas traseras
        self.r = .04  # radio de las ruedas
        
        self.timer = self.create_timer(self.t_s, self.timer_callback)
        self.v_x = 0
        self.w_z = 0
        self.theta_l = 0
        self.theta_r = 0
        self.time_1=self.get_clock().now()


    def cmd_vel_callback(self,msg):
        """
        Esta funciòn recibe el tópico para comandar el robot
        """
        self.v_x = msg.linear.x 
        self.w_z = msg.angular.z

    def clamp(self,num, min_value, max_value):
        """
        Función para limitar el valor de las señales
        """
        return max(min(num, max_value), min_value)
    def timer_callback(self):
        """
        Esta función es periodica y es la encargada de enviar el comando y recibir la información del serial
        """
        

        w_ld = 1/self.r * (self.v_x - self.L*self.w_z)
        w_rd = 1/self.r * (self.v_x + self.L*self.w_z)
        my_time = self.get_clock().now()
        
        delta_t =(my_time-self.time_1).nanoseconds/1000000000
        if not self.simulation:
            None
            w_l_=int(self.clamp(w_ld*10,0,255))
            w_r_=int(self.clamp(w_rd*10,0,255))
            command = 1
            comandos = 'z='+str(command)+' vl='+str(w_l_)+' vr='+str(w_r_)+'\n'
            self.ser.write(comandos.encode())
            #lectura de los datos
            line=self.ser.read_until().decode("utf-8")
            
            self.w_l = -1.0
            self.w_r = -1.0
            if len(line)>0:
                datos=line[:-2].split(',')
                
                if len(datos)==3:
                    self.w_l = float(datos[0])/10.
                    self.w_r = float(datos[1])/10.
                    print(self.w_l,self.w_r)
                    #TODO: use datos[2]=time para errores y usar try except 
                else:
                    print("error de recepción de datos")
                
            else:
                print('error de recepción de datos')
            self.theta_l += self.w_l * delta_t
            self.theta_r += self.w_r * delta_t 
            
        else:
            #modelo cinemático para simular el robot
            self.w_l = w_ld
            self.w_r = w_rd
            self.theta_l += self.w_l * delta_t
            self.theta_r += self.w_r * delta_t 

        #TODO: adicionar el nombre de los joint the cada rueda del urdf
        joints = JointState()
        joints.header = Header()
        joints.header.frame_id = "base_link"
        joints.name = ['l_tyre', 'r_tyre']
        joints.position = [self.theta_l, self.theta_r]
        joints.velocity = [self.w_l, self.w_r]
        joints.effort = [-1.0,-1.0]
        self.joint_state_pub_.publish(joints)
        self.time_1 = my_time


def main(args=None):
    rclpy.init(args=args)

    axioma_node = AxiomaNode()

    rclpy.spin(axioma_node)

    # Destroy the node explicitly (optional)
    axioma_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
