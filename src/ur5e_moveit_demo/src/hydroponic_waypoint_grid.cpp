#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <moveit/robot_state/robot_state.hpp>

int main(int argc, char** argv)
{
  // Initialize ROS 2
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("hydroponic_waypoint_grid");

  // Create a single-threaded executor to spin the node
  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(node);

  // Start a separate thread for spinning
  std::thread([&executor]() { executor.spin(); }).detach();

  // Initialize MoveGroupInterface for the UR5e manipulator
  moveit::planning_interface::MoveGroupInterface move_group(node, "ur_manipulator");

  // Optional settings for motion planning
  move_group.setPlanningTime(5.0);
  move_group.setMaxVelocityScalingFactor(0.1);
  move_group.setMaxAccelerationScalingFactor(0.1);

  // Get the current joint model group
  const moveit::core::JointModelGroup* joint_model_group =
      move_group.getCurrentState()->getJointModelGroup("ur_manipulator");

  // Get the current state of the robot
  moveit::core::RobotStatePtr current_state = move_group.getCurrentState(10.0);
  std::vector<double> joint_group_positions;
  current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);

  // Set target joint values
  joint_group_positions[0] = 0.00; // shoulder pan
  joint_group_positions[1] = -1.5708; // shoulder lift
  joint_group_positions[2] = 1.5708; // elbow
  joint_group_positions[3] = -1.5708; // wrist 1
  joint_group_positions[4] = -1.5708; // wrist 2
  joint_group_positions[5] = 3.14; // wrist 3

  move_group.setJointValueTarget(joint_group_positions);

  // Plan and execute
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  bool success = (move_group.plan(my_plan) == moveit::core::MoveItErrorCode::SUCCESS);

  if (success) {
    RCLCPP_INFO(node->get_logger(), "Plan successful, executing...");
    move_group.execute(my_plan);
  } else {
    RCLCPP_ERROR(node->get_logger(), "Planning failed!");
  }

  geometry_msgs::msg::Pose target_pose = move_group.getCurrentPose().pose;
  target_pose.orientation.x;
  target_pose.orientation.y;
  target_pose.orientation.z;
  target_pose.orientation.w;
  target_pose.position.x;
  target_pose.position.y;
  target_pose.position.z;
  
  std::vector<geometry_msgs::msg::Pose> approach_waypoints;
  ////////////////////////////////////////////////////////////////
  for (int i = 0; i < 10; i++)
  {
    target_pose.position.x -= 0.1016/10;
    approach_waypoints.push_back(target_pose);
  }
  moveit_msgs::msg::RobotTrajectory trajectory_approach;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;

  double fraction = move_group.computeCartesianPath(
    approach_waypoints, eef_step, jump_threshold, trajectory_approach);

  if (fraction > 0.9)
  {
    move_group.execute(trajectory_approach);
  }
  else
  {
    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Cartesian path planning failed: %.2f%% completed", fraction * 100.0);
  }
  approach_waypoints.clear();
    
  ////////////////////////////////////////////////////////////////////
  for (int i = 0; i < 10; i++)
  {
    target_pose.position.y += 0.0762/10;
    approach_waypoints.push_back(target_pose);
  }
  fraction = move_group.computeCartesianPath(
    approach_waypoints, eef_step, jump_threshold, trajectory_approach);
  if (fraction > 0.9)
    {
      move_group.execute(trajectory_approach);
    }
  else
  {
    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Cartesian path planning failed: %.2f%% completed", fraction * 100.0);
  }
  approach_waypoints.clear();

  ////////////////////////////////////////////////////////////////////
  for (int i = 0; i < 10; i++)
  {
    target_pose.position.y += 0.152/10;
    approach_waypoints.push_back(target_pose);
  }
  fraction = move_group.computeCartesianPath(
    approach_waypoints, eef_step, jump_threshold, trajectory_approach);
  if (fraction > 0.9)
    {
      move_group.execute(trajectory_approach);
    }
  else
  {
    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Cartesian path planning failed: %.2f%% completed", fraction * 100.0);
  }
  approach_waypoints.clear();

  ////////////////////////////////////////////////////////////////////
  for (int i = 0; i < 10; i++)
  {
    target_pose.position.y += 0.0762/10;
    approach_waypoints.push_back(target_pose);
  }
  fraction = move_group.computeCartesianPath(
    approach_waypoints, eef_step, jump_threshold, trajectory_approach);
  if (fraction > 0.9)
    {
      move_group.execute(trajectory_approach);
    }
  else
  {
    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Cartesian path planning failed: %.2f%% completed", fraction * 100.0);
  }
  approach_waypoints.clear();

  ////////////////////////////////////////////////////////////////////
  for (int i = 0; i < 10; i++)
  {
    target_pose.position.x += 0.1016/10;
    approach_waypoints.push_back(target_pose);
  }
  fraction = move_group.computeCartesianPath(
    approach_waypoints, eef_step, jump_threshold, trajectory_approach);
  if (fraction > 0.9)
    {
      move_group.execute(trajectory_approach);
    }
  else
  {
    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Cartesian path planning failed: %.2f%% completed", fraction * 100.0);
  }
  approach_waypoints.clear();

  ////////////////////////////////////////////////////////////////////
  for (int i = 0; i < 10; i++)
  {
    target_pose.position.x += 0.1016/10;
    approach_waypoints.push_back(target_pose);
  }
  fraction = move_group.computeCartesianPath(
    approach_waypoints, eef_step, jump_threshold, trajectory_approach);
  if (fraction > 0.9)
    {
      move_group.execute(trajectory_approach);
    }
  else
  {
    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Cartesian path planning failed: %.2f%% completed", fraction * 100.0);
  }
  approach_waypoints.clear();

   

  
  // Shutdown
  rclcpp::shutdown();
  return 0;
}
