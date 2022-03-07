# programar

- Assumindo que o workspace esta no ~/lms_ws/
- criar o pacote
	cd ~/lms_ws/src
	ros2 pkg create --build-type ament_python py_basic_examples
- Criar codigo min_publisher.py na pasta ~/lms_ws/src/py_basic_examples/py_basic_examples

```
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class MinimalPublisher(Node):

    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(String, 'mensagem', 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = String()
        msg.data = 'Hello World: %d' % self.i
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)
        self.i += 1


def main(args=None):
    rclpy.init(args=args)
    minimal_publisher = MinimalPublisher()
    rclpy.spin(minimal_publisher)
    # Destroy the node explicitly(optional)
    minimal_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
```
- Criar codigo min_subscriber.py na pasta ~/lms_ws/src/py_basic_examples/py_basic_examples
```
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class MinimalSubscriber(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription = self.create_subscription(
            String,
            'mensagem',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.data)

def main(args=None):
    rclpy.init(args=args)
    minimal_subscriber = MinimalSubscriber()
    rclpy.spin(minimal_subscriber)
    # Destroy the node explicitly (optional)
    minimal_subscriber.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
```

- abrir o arquivo ~/lms_ws/src/py_basic_examples/package.xml e modificar as informacoes gerais do pacote


- configurar o executable no arquivo ~/lms_ws/src/py_basic_examples/setup.py
```
entry_points={
        'console_scripts': [
                'talker = py_basic_examples.min_publisher:main',
                'listener = py_basic_examples.min_subscriber:main',
        ],
},
```
- O arquivo setup.cfg configura para ro2 run onde vai ficar o pacote (em teoria n~ao temos que modificar ele)

- Você deve ter instalado os pacotes requeridos(*rclpy* e *std_msgs*), mas como boa pratica e melhor executar `rosdep`.
	cd ~/lms_ws/
	rosdep install -i --from-path src/py_basic_examples --rosdistro foxy -y

- compilar para gerar o "executable" no lugar onde ros vai achar
	cd ~/lms_ws/
	colcon build --packages-select py_basic_examples


## teste

- iniciar o publisher em uma consola
	source ~/lma_ws/install/setup.bash
	ros2 run py_basic_examples talker
	


__ns:=/scooby 
## Ligando com scooby

vamos a guardar o arquivo min_publisher.py como circle_scooby.py e fazer o seguinte:
- assumindo que você tem o pacote scooby_gazebo
- adicionar a libraria
	from geometry_msgs.msg import Twist
- cambiar o nome do nó:
	super().__init__('scooby_circle')
- trocar o tipo de mensagen e o nome do topico
	self.publisher_ = self.create_publisher(Twist, 'scooby/cmd_vel', 10)

- modificar o metodo `timer_callback` para enviar o mensagem certo.
```
    def timer_callback(self):
        msg = Twist()
        msg.linear.x = 0.5
        msg.angular.z = 0.5
        self.publisher_.publish(msg)
        self.get_logger().info(f'linear vel: {msg.linear.x}, angular vel {msg.angular.z}' )
        self.i += 1
```
- modificar o arquivo *package.xml* para adicionar o pacote `geometry_msgs`
 
	<exec_depend>geometry_msgs<exec_depend>

- agregar o executable no *setup.py*
```
'console_scripts': [
                'talker = py_basic_examples.min_publisher:main',
                'listener = py_basic_examples.min_subscriber:main',
                'scooby_circle = py_basic_examples.circle_scooby:main',
        ],
```
- executar o script

- executar o robo
	ros2 launch scooby_gazebo odom_imu.launch.py world:=scooby_factory_v1.world

  No caso de nao ter o scooby pode usar o turtlesim
	ros2 run turtlesim turtlesim_node --ros-args --remap turtle1/cmd_vel:=scooby/cmd_vel


