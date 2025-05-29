#include "BebopTeleop.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

BebopTeleop::BebopTeleop() : Node("bebop_teleop_node") {
	RCLCPP_INFO(this->get_logger(), "Initializing Bebop Teleop Node");

    // Joy button config
    this->declare_parameter("x_axis", -1);
    this->declare_parameter("y_axis", -1);
    this->declare_parameter("z_axis", -1);
    this->declare_parameter("yaw_axis", -1);

    this->declare_parameter("x_vel_max", 1.0);
    this->declare_parameter("y_vel_max", 1.0);
    this->declare_parameter("z_vel_max", 1.0);
    this->declare_parameter("yaw_vel_max", 1.0);

    this->get_parameter("x_axis", axes_.x.axis);
    this->get_parameter("y_axis", axes_.y.axis);
    this->get_parameter("z_axis", axes_.z.axis);
    this->get_parameter("yaw_axis", axes_.yaw.axis);

    this->get_parameter("x_vel_max", axes_.x.factor);
    this->get_parameter("y_vel_max", axes_.y.factor);
    this->get_parameter("z_vel_max", axes_.z.factor);
    this->get_parameter("yaw_vel_max", axes_.yaw.factor);

    RCLCPP_INFO(this->get_logger(), "Loaded controller axis parameters:\nX: %d, Y: %d, Z: %d, Yaw: %d", axes_.x.axis, axes_.y.axis, axes_.z.axis, axes_.yaw.axis);

    joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>("joy", 10, std::bind(&BebopTeleop::joy_callback, this, _1));
}

void BebopTeleop::joy_callback(const sensor_msgs::msg::Joy::SharedPtr joy_msg) {

}

// void BebopTeleop::flying_state_callback(const bebop_msgs::Ardrone3PilotingStateFlyingStateChangedConstPtr &state_msg) {
//     //Update the flying state
//     flying_state_ = static_cast<bebop_flying_state>(state_msg->state);

//     switch(flying_state_) {
//     case landed:
//         ROS_WARN("%s BebopController: Switched to landed state!", bebop_prefix_.c_str());
//         break;
//     case taking_off:
//         ROS_WARN("%s BebopController: Switched to takeoff state!", bebop_prefix_.c_str());
//         break;
//     case hovering:
//         ROS_WARN("%s BebopController: Switched to hover state!", bebop_prefix_.c_str());
//         break;
//     case flying:
//         ROS_WARN("%s BebopController: Switched to flying state!", bebop_prefix_.c_str());
//         break;
//     case landing:
//         ROS_WARN("%s BebopController: Switched to landing state!", bebop_prefix_.c_str());
//         break;
//     case emergency:
//         ROS_ERROR("%s BebopController: Switched to emergency state!", bebop_prefix_.c_str());
//         break;
//     case user_takeoff:
//         ROS_WARN("%s BebopController: Switched to user takeoff state!", bebop_prefix_.c_str());
//         break;
//     case motor_ramping:
//         ROS_WARN("%s BebopController: Switched to motor ramping state!", bebop_prefix_.c_str());
//         break;
//     case emergency_landing:
//         ROS_ERROR("%s BebopController: Switched to emergency landing state!", bebop_prefix_.c_str());
//         break;
//     default:
//         ROS_WARN("%s BebopController: Invalid state received.", bebop_prefix_.c_str());
//     }
// }
