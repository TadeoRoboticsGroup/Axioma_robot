# Copyright 2021 Olmer Garcia
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

"""Start robot state publisher node for scooby robot."""

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription,TimerAction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():

    scooby_description_pkg=get_package_share_directory('scooby_description')
    use_robot_state_pub = LaunchConfiguration('use_robot_state_pub')
    use_rviz = LaunchConfiguration('use_rviz')
    urdf_file= LaunchConfiguration('urdf_file')

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{'use_sim_time': True}],
        # remappings=[
        #     ("joint_states", "scooby/joint_states")
        # ],
        arguments=[urdf_file])

    rviz = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', os.path.join(scooby_description_pkg, 'rviz', 'scooby.rviz')],
        condition=IfCondition(use_rviz)
    )
        
    ld = LaunchDescription([
        DeclareLaunchArgument('use_rviz', default_value='true',
                              description='Open RViz.'),
        DeclareLaunchArgument('urdf_file',default_value=os.path.join(scooby_description_pkg, 'urdf', 'scooby.urdf'),
                              description='urddeclare_urdf_cmd =f file complete path'),                   
        robot_state_publisher,
        rviz
    ])
    return ld
