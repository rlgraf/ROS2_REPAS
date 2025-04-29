#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <moveit/robot_state/robot_state.hpp>

int main(int argc, char** argv)
{
  // Initialize ROS 2
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("home");

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
  joint_group_positions[0] = 0.00;
  joint_group_positions[1] = -2.50;
  joint_group_positions[2] = 1.50;
  joint_group_positions[3] = -2.00;
  joint_group_positions[4] = -1.55;
  joint_group_positions[5] = 0.00;

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

  // Shutdown
  rclcpp::shutdown();
  return 0;
}
