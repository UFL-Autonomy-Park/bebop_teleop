#ifndef BEBOP_TELEOP_HPP
#define BEBOP_TELEOP_HPP

#include <rclcpp/rclcpp.hpp>

#include <sensor_msgs/msg/joy.hpp>

class BebopTeleop : public rclcpp::Node {
private:
	rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;

	std::string bebop_id_;

    // Controller axis and button structs
    struct Axis {
        Axis() : axis(0), factor(0.0), offset(0.0) {}

        int axis;
        double factor;
        double offset;
    };

    struct {
        Axis x;
        Axis y;
        Axis z;
        Axis yaw;
    } axes_;

    struct Button {
        Button() : button(0) {}
        int button;
    };

    struct {
        Button takeoff;
        Button land;
    } buttons_;

    //Button state for debouncing
    struct ButtonState {
        ButtonState() : state(0) {}
        int state;
    };

    struct {
        ButtonState takeoff;
        ButtonState land;
    } button_state_;

    enum bebop_flying_state {
        landed = 0,
        taking_off,
        hovering,
        flying,
        landing,
        emergency,
        user_takeoff,
        motor_ramping,
        emergency_landing
    };

    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr joy_msg);

    // void flying_state_callback(const bebop_msgs::Ardrone3PilotingStateFlyingStateChangedConstPtr &flying_state_msg);

public:
	BebopTeleop();
};

#endif