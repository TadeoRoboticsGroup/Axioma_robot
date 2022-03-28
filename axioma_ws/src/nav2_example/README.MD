## Creating a minimal example with turtlesim and Nav2

This example generate a tf for the turtlesim and configure nav2, without slam to planning and control the robot
in an open area.

1. create a package
        cd ~lma_ws/src
        ros2 pkg create --build-type ament_cmake nav2_example
2. inside nav2_examples/src create  turtlesim_tf2.cpp and copy



3. Modify package.xml with your data and add the dependecies

        ```
        <depend>rclcpp</depend>
        <depend>turtlesim</depend>
        <depend>tf2</depend>
        <depend>tf2_ros</depend>
        <depend>tf2_msgs</depend>
        <depend>geometry_msgs</depend>
        ```

4. Modify CmakeLists.txt to add dependencies, create the executable and install
        find_package(rclcpp REQUIRED)
        find_package(tf2 REQUIRED)
        find_package(tf2_ros REQUIRED)
        find_package(tf2_msgs REQUIRED)
        find_package(geometry_msgs REQUIRED)
        find_package(rclcpp REQUIRED)
        find_package(turtlesim REQUIRED)
        ...
        add_executable(turtlesim_tf2 src/turtlesim_tf2.cpp)
        ament_target_dependencies(
                turtlesim_tf2 
                rclcpp 
                tf2 
                tf2_ros
                tf2_msgs
                geometry_msgs 
                turtlesim
                )
        ...
        install(TARGETS
                turtlesim_tf2
        DESTINATION lib/${PROJECT_NAME})

5. We will have the next files
 - my_world.pgm  1109x1109 gray scale image with open space(low gray)
 - my_world.yaml  characteristic of the map: 
   - resolution m/pixel
   - origin of the image in map space [x,y,theta]
   - the value of the grid should be minor that > occupied_thresh or < free_thresh 
 - my_nav2_params.yaml [IN PROGRESS TO UNDERSTAND]

6. Add param, launch and rviz folders in CMakeLists.txt
        install(DIRECTORY
                launch
                DESTINATION share/${PROJECT_NAME}/
        )

        install(DIRECTORY
                param
                DESTINATION share/${PROJECT_NAME}/
        )

        install(DIRECTORY
                rviz
                DESTINATION share/${PROJECT_NAME}/
        )

7. install nav2 
        sudo apt-get install ros-foxy-nav2-*

8. build turtlesim_tf node, which will generate the ideal /odom and /map frames for turtlesim
                cd ~lma_ws
                colcon build
9. run
        ros2 launch nav2_example turtlesim_nav2_launch.py


## Scooby Nav2 without laser(just odometry)

1. Make a node to generate the map frame (scooby_map_tf2.cpp)

2. modify package.xml to add the dependency to nav_msgs::odom
        <depend>nav_msgs</depend>

3. Modify CMakeLists.txt to add the dependencies and the new node
        find_package(nav_msgs REQUIRED)
        ...
        add_executable(scooby_map_tf2 src/scooby_map_tf2.cpp)
        ament_target_dependencies(
                scooby_map_tf2 
                rclcpp 
                tf2 
                tf2_ros
                tf2_msgs
                nav_msgs
        )
4. Modify the launch (scooby_nav2_launch.py)
  - remove turtlesim and turtlesim_tf2 action
  - add an action for scooby_map_tf2
  - add an action for scooby_ros from package *motors_node*
  - add an action for robot_state_publisher
  - change default value of namespace to scooby (`default_value='scooby'`) ad add all to this namespace
  - remap tf and tf_static for be inside the namespace (not better way to do?)

5. Execute the new launch file
   ros2 launch nav2_example scooby_nav2_launch.py

## nav2 + gazebo com LIDAR

1. instalado no ws o pacote de scooby
2. compilar
3. adicionar o bash
4. executar
        ros2 launch nav2_example scooby_gazebo_nav2_launch.py
5. No rviz asignar a posicao inicial do robo com o botao 2D pose Estimate (ele publica no topico scooby/initialpose)

6. Na barra de ferramentas dar click em "D goal pose

7. pronto o robo no gazebo deve chegar no destino



instalar nav2
sudo apt-get install ros-foxy-nav2-bringup ros-foxy-navigation2

olmerg