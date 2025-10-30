#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <moveit/robot_state/robot_state.hpp>
#include <moveit_msgs/msg/collision_object.hpp>
#include <shape_msgs/msg/solid_primitive.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <vector>
#include <chrono>
#include <thread>

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

  ////// Start the box

  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  std::vector<moveit_msgs::msg::CollisionObject> collision_objects;

  // Units in meters (inches * 0.0254)
  double box_center_x = -36.75 * 0.0254;
  double box_center_y = -5.5 * 0.0254;
  double box_center_z = 17.5 * 0.0254;

  double box_x = 17.0 * 0.0254;   // Forward/backward length
  double box_y = 25.5 * 0.0254;   // Width
  double box_z = 21.0 * 0.0254;   // Height

  double wall_thickness = 0.01;   // Thin walls
  std::string frame_id = "base_link";  // Frame of reference

  struct Wall {
    std::string id;
    double size_x, size_y, size_z;
    double pos_x, pos_y, pos_z;
  };

  std::vector<Wall> walls = {
    //Front wall (farthest from robot)
    {"front_wall", wall_thickness, box_y, box_z,
     box_center_x + box_x / 2.0 + 0.1, box_center_y, box_center_z},

    // Left wall
    {"left_wall", box_x, wall_thickness, box_z,
     box_center_x, box_center_y + box_y / 2.0, box_center_z},

    // Right wall
    {"right_wall", box_x, wall_thickness, box_z,
     box_center_x, box_center_y - box_y / 2.0, box_center_z},

    // Ceiling
    {"ceiling", box_x, box_y, wall_thickness,
     box_center_x, box_center_y, box_center_z + box_z / 2.0},

    // Floor
    {"floor", box_x, box_y, wall_thickness,
     box_center_x, box_center_y, box_center_z - box_z / 2.0},
  };

  for (const auto& wall : walls) {
    moveit_msgs::msg::CollisionObject obj;
    obj.header.frame_id = frame_id;
    obj.id = wall.id;

    shape_msgs::msg::SolidPrimitive primitive;
    primitive.type = primitive.BOX;
    primitive.dimensions = {wall.size_x, wall.size_y, wall.size_z};

    geometry_msgs::msg::Pose pose;
    pose.position.x = wall.pos_x;
    pose.position.y = wall.pos_y;
    pose.position.z = wall.pos_z;
    pose.orientation.w = 1.0;

    obj.primitives.push_back(primitive);
    obj.primitive_poses.push_back(pose);
    obj.operation = obj.ADD;

    collision_objects.push_back(obj);
  }

  planning_scene_interface.applyCollisionObjects(collision_objects);

  ///// end box setup

  // Get the current joint model group
  const moveit::core::JointModelGroup* joint_model_group =
      move_group.getCurrentState()->getJointModelGroup("ur_manipulator");

  // Get the current state of the robot
  moveit::core::RobotStatePtr current_state = move_group.getCurrentState(10.0);
  std::vector<double> joint_group_positions;
  current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);

  // Set target joint values
  joint_group_positions[0] = -3.14; // shoulder pan
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

  geometry_msgs::msg::Pose start_pose = move_group.getCurrentPose().pose;
  start_pose.orientation.x;
  start_pose.orientation.y;
  start_pose.orientation.z;
  start_pose.orientation.w;
  start_pose.position.x;
  start_pose.position.y;
  start_pose.position.z;

  // SET HEIGHT

  double z = -9*0.0254;

  double target_pose_z = start_pose.position.z + z;
  std::vector<geometry_msgs::msg::Pose> waypoints_z;

  for (int j = 0; j < 10; j++){
      geometry_msgs::msg::Pose waypoint_z = start_pose;
      waypoint_z.position.z += (target_pose_z - start_pose.position.z) * (j / 10.0);
      waypoints_z.push_back(waypoint_z);
    }
    moveit_msgs::msg::RobotTrajectory trajectory_approach_z;
    const double jump_threshold_z = 0.0;
    const double eef_step_z = 0.01;

    double fraction = move_group.computeCartesianPath(
    waypoints_z, eef_step_z, jump_threshold_z, trajectory_approach_z);

    if (fraction > 0.9)
    {
        move_group.execute(trajectory_approach_z);
    }
    else
    {
        RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Cartesian path planning failed: %.2f%% completed", fraction * 100.0);
    }
    waypoints_z.clear();
  


// DEFINE PATH

  struct Node {
  double x;
  double y;
  };

  //Node N1 = {-2, 10.5};
  //Node N2 = {6, 10.5};
  //Node N3 = {2, 7.5};
  //Node N4 = {-6, 7.5};
  //Node N5 = {-2, 4.5};
  //Node N6 = {6, 4.5};
  //Node N7 = {2, 1.5};
  //Node N8 = {-6, 1.5};
  //Node N9 = {-2, -1.5};
  //Node N10 = {6, -1.5};
  //Node N11 = {2, -4.5};
  //Node N12 = {-6, -4.5};
  //Node N13 = {-2, -7.5};
  //Node N14 = {6, -7.5};
  //Node N15 = {2, -10.5};
  //Node N16 = {-6, -10.5};

  //Node N1 = {0, 0};
  Node N1 = {-8, 11};
  Node N2 = {0, 11};
  Node N3 = {8, 11};
  Node N4 = {8, 4};
  Node N5 = {0, 4};
  Node N6 = {-8, 4};
  Node N7 = {-8, -4};
  Node N8 = {0, -4};
  Node N9 = {8, -4};
  Node N10 = {8, -11};
  Node N11 = {0, -11};
  Node N12 = {-8, -11};

  //Node N1 = {0, 0}

  std::vector<Node> nodes = {N1, N2, N3, N4, N5, N6, N7, N8, N9, N10, N11, N12};

  for (size_t i = 0; i < nodes.size(); ++i) {
    double x_pos = nodes[i].x*0.0254;
    double y_pos = nodes[i].y*0.0254;

    geometry_msgs::msg::Pose current_pose = move_group.getCurrentPose().pose;
    
    geometry_msgs::msg::Pose target_pose = start_pose;
    target_pose.position.x += x_pos;
    target_pose.position.y += y_pos;
    std::vector<geometry_msgs::msg::Pose> waypoints;
 
    for (int j = 0; j < 10; j++){
      geometry_msgs::msg::Pose waypoint = current_pose;
      waypoint.position.x += (target_pose.position.x - current_pose.position.x) * (j / 10.0);
      waypoint.position.y += (target_pose.position.y - current_pose.position.y) * (j / 10.0);
      waypoints.push_back(waypoint);
    }
    moveit_msgs::msg::RobotTrajectory trajectory_approach;
    const double jump_threshold = 0.0;
    const double eef_step = 0.01;

    double fraction = move_group.computeCartesianPath(
    waypoints, eef_step, jump_threshold, trajectory_approach);

    if (fraction > 0.9)
    {
        move_group.execute(trajectory_approach);
    }
    else
    {
        RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Cartesian path planning failed: %.2f%% completed", fraction * 100.0);
    }
    waypoints.clear();
    rclcpp::sleep_for(std::chrono::seconds(1));
  }

  joint_group_positions[0] = -3.14; // shoulder pan
  joint_group_positions[1] = -1.5708; // shoulder lift
  joint_group_positions[2] = 1.5708; // elbow
  joint_group_positions[3] = -1.5708; // wrist 1
  joint_group_positions[4] = -1.5708; // wrist 2
  joint_group_positions[5] = 3.14; // wrist 3

  move_group.setJointValueTarget(joint_group_positions);

  // Plan and execute
  success = (move_group.plan(my_plan) == moveit::core::MoveItErrorCode::SUCCESS);

  if (success) {
    RCLCPP_INFO(node->get_logger(), "Plan successful, executing...");
    move_group.execute(my_plan);
  } 
  else {
    RCLCPP_ERROR(node->get_logger(), "Planning failed!");
  }

  // Shutdown
  rclcpp::shutdown();
  return 0;
}