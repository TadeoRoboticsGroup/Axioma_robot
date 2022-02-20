import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():

  use_sim_time = LaunchConfiguration('axioma_urdf', default='false')
  urdf_file_name = 'urdf/robot_axioma.urdf'

  print("urdf_file_name : {}".format(urdf_file_name))

  urdf = os.path.join(
      get_package_share_directory('axioma_urdf'),
      urdf_file_name)

  return LaunchDescription([

        DeclareLaunchArgument(
            'axioma_urdf',
            default_value='false',
            description='Use simulation (Gazebo) clock if true'),

        # ExecuteProcess(
        #     cmd=["ros2", "launch", "gazebo_ros", "gazebo.launch.py"]
        # ),

        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            parameters=[{'use_sim_time': use_sim_time}],
            arguments=[urdf]),

        Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            name='urdf_spawner',
            output='screen',
            arguments=["-topic", "/robot_description", "-entity", "cam_bot"])
  ])
