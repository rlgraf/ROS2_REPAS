#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>

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
  target_pose.orientation.x = 0.0;
  target_pose.orientation.y = 1.0;
  target_pose.orientation.z = 1.0;
  target_pose.orientation.w = 0.5;
  target_pose.position.x = 0.3;
  target_pose.position.y = 0.3;
  target_pose.position.z = 0.4;
  move_group.setPoseTarget(target_pose);
  
  
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  bool success = static_cast<bool>(move_group.plan(my_plan));

  std::vector<geometry_msgs::msg::Pose> approach_waypoints;
  target_pose.position.z -= 0.03;
  approach_waypoints.push_back(target_pose);

  target_pose.position.z -= 0.03;
  approach_waypoints.push_back(target_pose);

  moveit_msgs::msg::RobotTrajectory trajectory_approach;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;

  double fraction = move_group.computeCartesianPath(
      approach_waypoints, eef_step, jump_threshold, trajectory_approach);

  move_group.execute(trajectory_approach);

  // Retreat

  std::vector<geometry_msgs::msg::Pose> retreat_waypoints;
  target_pose.position.z += 0.03;
  retreat_waypoints.push_back(target_pose);

  target_pose.position.z += 0.03;
  retreat_waypoints.push_back(target_pose);

  moveit_msgs::msg::RobotTrajectory trajectory_retreat;

  fraction = move_group.computeCartesianPath(
      retreat_waypoints, eef_step, jump_threshold, trajectory_retreat);

  move_group.execute(trajectory_retreat);

  rclcpp::shutdown();
  return 0;
}
