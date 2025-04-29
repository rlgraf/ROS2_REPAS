#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("move_ur5e_node");

  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(node);

  moveit::planning_interface::MoveGroupInterface move_group(node, "ur_manipulator");

  move_group.setPlanningTime(5.0);
  move_group.setMaxVelocityScalingFactor(0.1);
  move_group.setMaxAccelerationScalingFactor(0.1);

  geometry_msgs::msg::Pose target_pose;
  target_pose.orientation.w = 1.0;
  target_pose.position.x = 0.3;
  target_pose.position.y = 0.2;
  target_pose.position.z = 0.4;
  move_group.setPoseTarget(target_pose);

  /*
  target_pose_orientation.x = 0.0;
  target_pose_orientation.y = 1.0;
  targert_pose_orientation.z = 0.0;
  target_pose.orientation.w = 0.0;
  target_pose.position.x = 0.4;
  target_pose.position.y = 0.0;
  target_pose.position.z = 0.4;
  move_group.setPoseTarget(target_pose);
  */

  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  bool success = static_cast<bool>(move_group.plan(my_plan));

  if (success) {
    RCLCPP_INFO(node->get_logger(), "Plan successful, executing...");
    move_group.execute(my_plan);
  } else {
    RCLCPP_ERROR(node->get_logger(), "Planning failed!");
  }

  rclcpp::shutdown();
  return 0;
}
