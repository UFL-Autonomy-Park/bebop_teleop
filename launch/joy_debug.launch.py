import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='joy',
            executable='joy_node',
            name='joy_node',
            parameters=[os.path.join(get_package_share_directory('bebop_teleop'), 'config', 'joy_config.yaml')],
            output='screen'
        ),
        Node(
            package='bebop_teleop',
            executable='bebop_teleop_node',
            name='bebop_teleop_node',
            parameters=[
                os.path.join(get_package_share_directory('bebop_teleop'), 'config', 'xbox_controller.yaml'),
            ],
            output='screen'
        ),
    ])