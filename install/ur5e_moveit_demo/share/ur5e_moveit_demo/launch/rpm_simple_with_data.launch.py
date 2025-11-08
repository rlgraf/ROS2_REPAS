from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    ur_simulation_gz_pkg = get_package_share_directory('ur_simulation_gz')
    ur_moveit_config_pkg = get_package_share_directory('ur_moveit_config')
    your_package = get_package_share_directory('ur5e_moveit_demo')

    return LaunchDescription([
        # 1. Launch Gazebo and MoveIt from ur_sim_moveit.launch.py
        
        #IncludeLaunchDescription(
        #    PythonLaunchDescriptionSource(
        #        os.path.join(ur_simulation_gz_pkg, 'launch', 'ur_sim_moveit.launch.py')
        #    ),
        #    launch_arguments={
        #        'use_fake_hardware': 'true',  # Useful for simulation
         #       'robot_ip': '127.0.0.1',      # Dummy IP for simulation
        #        'launch_rviz': 'true'         # Launch RViz by default
        #   }.items()
        #),
    
        # 2. Launch your MoveIt motion script (after a small delay)
        TimerAction(
            period=5.0,
            actions=[
                Node(
                    package='ur5e_moveit_demo',
                    executable='rpm_simple_with_data',
                    name='rpm_simple_with_data',
                    output='screen',
                    parameters=[{'use_sim_time': True}]
                )
            ]
        )
    ])
