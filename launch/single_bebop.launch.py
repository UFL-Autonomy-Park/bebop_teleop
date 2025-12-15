import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def cfg_path(pkg, sub, filename):
    return os.path.join(get_package_share_directory(pkg), sub, filename)

def generate_launch_description():
    BEBOP_CONTROL_CFG = cfg_path('bebop_control', 'param', 'bebop_param.yaml')
    FILTERS_CFG = cfg_path('mocap_filters', 'config', 'filter_params.yaml')
    TELEOP_JOY_CFG = cfg_path('bebop_teleop', 'param', 'joy_config.yaml')
    TELEOP_XBOX_CFG = cfg_path('bebop_teleop', 'param', 'xbox_controller.yaml')
    VRPN_CLIENT_CFG = cfg_path('vrpn_mocap', 'config', 'client.yaml')
    FIGURE_EIGHT_CFG = cfg_path('bebop_trajectory_tracking', 'param', 'figure_eight_param.yaml')
    
    # RViz configuration path
    RViz_CFG = cfg_path('bebop_trajectory_tracking', 'param', 'bebop_view.rviz')

    # Constants
    BEBOP_NS = 'bebop104'
    VRPN_SERVER_IP = '192.168.1.201'
    VRPN_SERVER_PORT = 3883

    # Parameter list for the bebop_driver node
    bebop_driver_params = [
        {'bebop_ip': '192.168.1.104'},
        {'camera_calibration_file': 'package://ros2_bebop_driver/config/bebop2_camera_calib.yaml'},
        {'max_tilt_angle': 15.0},
        {'max_rotation_speed': 200.0},
    ]

    return LaunchDescription([
        Node(
            package='vrpn_mocap',
            executable='client_node',
            name='vrpn_mocap_client_node',
            namespace='vrpn_mocap',
            parameters=[VRPN_CLIENT_CFG, {'server': VRPN_SERVER_IP}, {'port': VRPN_SERVER_PORT}],
            output='screen'
        ),
        Node(
            package='joy',
            executable='joy_node',
            name='joy_node',
            parameters=[TELEOP_JOY_CFG],
            output='screen'
        ),
        Node(
            package='ros2_bebop_driver',
            executable='bebop_driver',
            name='bebop_driver_node',
            namespace=BEBOP_NS,
            parameters=bebop_driver_params
        ),
        Node(
            package='bebop_teleop',
            executable='bebop_teleop_node',
            name='bebop_teleop_node',
            namespace=BEBOP_NS,
            parameters=[TELEOP_XBOX_CFG],
            output='screen'
        ),
        Node(
            package='mocap_filters',
            executable='filters_node',
            name='mocap_filters_node',
            output='screen',
            parameters=[FILTERS_CFG]
        ),
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            output='screen',
            arguments=['-d', RViz_CFG]
        ),
        Node(
            package='bebop_trajectory_tracking',
            executable='figure_eight',
            name='figure_eight_node',
            parameters=[FIGURE_EIGHT_CFG],
            output='screen'
        ),
        Node(
            package='bebop_control',
            executable='bebop_control_node',
            name='bebop_control_node',
            output='screen',
            parameters=[BEBOP_CONTROL_CFG]
        )
    ])