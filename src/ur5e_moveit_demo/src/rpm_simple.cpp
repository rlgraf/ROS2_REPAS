#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_ros/tf2_ros/buffer_interface.hpp>
#include <random>

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("rpm_simple");

  // Initialize MoveIt interface
  moveit::planning_interface::MoveGroupInterface move_group(node, "ur_manipulator");
  move_group.setPlanningTime(2.0);
  move_group.setMaxVelocityScalingFactor(0.3);
  move_group.setMaxAccelerationScalingFactor(0.3);

  // Random number generators
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> pos_x_dist(0.4, 0.55);
  std::uniform_real_distribution<> pos_y_dist(-0.2, 0.2);
  std::uniform_real_distribution<> pos_z_dist(0.35, 0.5);// safe height range
  std::uniform_real_distribution<> quat_dist(-1.0, 1.0);  // random quaternion components

  geometry_msgs::msg::Pose target_pose;

  while (rclcpp::ok())
  {
    bool reachable = false;

    while (!reachable)
    {
      // Random position in front of robot
      target_pose.position.x = pos_x_dist(gen);
      target_pose.position.y = pos_y_dist(gen);
      target_pose.position.z = pos_z_dist(gen);

      // Random quaternion
      tf2::Quaternion q(quat_dist(gen), quat_dist(gen), quat_dist(gen), quat_dist(gen));
      q.normalize();
      target_pose.orientation = tf2::toMsg(q);

      // Check if IK is solvable for this pose
      move_group.setStartStateToCurrentState();
      move_group.setPoseTarget(target_pose);

      moveit::planning_interface::MoveGroupInterface::Plan plan;
      if (move_group.plan(plan) == moveit::core::MoveItErrorCode::SUCCESS)
      {
        reachable = true;
        RCLCPP_INFO(node->get_logger(), "Found reachable random orientation!");
        move_group.execute(plan);
      }
      else
      {
        RCLCPP_DEBUG(node->get_logger(), "Random pose not reachable, retrying...");
      }
    }

    rclcpp::sleep_for(std::chrono::seconds(2));
  }

  rclcpp::shutdown();
  return 0;
}

