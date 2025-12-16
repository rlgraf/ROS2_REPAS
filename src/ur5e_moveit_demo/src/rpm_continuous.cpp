#include <rclcpp/rclcpp.hpp>
#include <trajectory_msgs/msg/joint_trajectory.hpp>
#include <trajectory_msgs/msg/joint_trajectory_point.hpp>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("base_velocity_circle");

    auto pub = node->create_publisher<trajectory_msgs::msg::JointTrajectory>(
        "/scaled_pos_joint_traj_controller/joint_trajectory", 10);

    RCLCPP_INFO(node->get_logger(), "Starting continuous base rotation with constant velocity...");

    std::vector<std::string> joint_names = {
        "shoulder_pan_joint",  // base joint
        "shoulder_lift_joint",
        "elbow_joint",
        "wrist_1_joint",
        "wrist_2_joint",
        "wrist_3_joint"
    };

    trajectory_msgs::msg::JointTrajectory traj_msg;
    traj_msg.joint_names = joint_names;

    double base_velocity = 0.2; // rad/s, adjust speed

    rclcpp::Rate rate(50); // 50 Hz loop
    while (rclcpp::ok())
    {
        trajectory_msgs::msg::JointTrajectoryPoint point;
        point.velocities = {base_velocity, 0, 0, 0, 0, 0};
        point.time_from_start = rclcpp::Duration::from_seconds(0.02); // 50 Hz
        traj_msg.points = {point};

        pub->publish(traj_msg);
        rclcpp::spin_some(node);
        rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
