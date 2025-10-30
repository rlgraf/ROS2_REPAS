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

#include <ament_index_cpp/get_package_share_directory.hpp>
#include <geometric_shapes/shape_operations.h>

int main(int argc, char** argv)
{
  // Initialize ROS 2
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("parlight_grid_with_cadsensor");

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


  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

// Load STL file as mesh
  auto node_base = node->get_node_base_interface();
  auto node_topics = node->get_node_topics_interface();
  auto node_services = node->get_node_services_interface();

  std::string package_path = ament_index_cpp::get_package_share_directory("ur5e_moveit_demo");
  std::string stl_path = "file://" + package_path + "/meshes/StructureResvrLightBox.stl";

  shapes::Mesh* m = shapes::createMeshFromResource(stl_path);
  if (!m)
  {
    RCLCPP_ERROR(node->get_logger(), "Failed to load mesh from %s", stl_path.c_str());
    return 1;
  }

  double scale = 0.001;  // mm → m
  for (unsigned int i = 0; i < m->vertex_count; ++i)
{
  m->vertices[3*i + 0] *= scale;  // x
  m->vertices[3*i + 1] *= scale;  // y
  m->vertices[3*i + 2] *= scale;  // z
}


  shape_msgs::msg::Mesh mesh_msg;
  shapes::ShapeMsg mesh_msg_tmp;
  shapes::constructMsgFromShape(m, mesh_msg_tmp);
  mesh_msg = boost::get<shape_msgs::msg::Mesh>(mesh_msg_tmp);

// Create collision object

  moveit_msgs::msg::CollisionObject collision_object;
  collision_object.header.frame_id = "base_link";  // usually "world" or "base_link"
  collision_object.id = "structure_reservoir";
  collision_object.meshes.push_back(mesh_msg);


  geometry_msgs::msg::Pose mesh_pose;
  mesh_pose.orientation.x = 0.0;
  mesh_pose.orientation.y = 0.0;
  mesh_pose.orientation.z = 1.0;
  mesh_pose.orientation.w = 0.0;

  mesh_pose.position.x = -0.037 - (33.75)*0.0254; // set appropriately
  mesh_pose.position.y = 0.048 + (12.875 - 5.5)*0.0254;
  mesh_pose.position.z = 0.0 - (2.75)*0.0254;

  collision_object.mesh_poses.push_back(mesh_pose);
  collision_object.operation = collision_object.ADD;

// Add the object to the planning scene
  //planning_scene_interface.applyCollisionObjects({collision_object});
  RCLCPP_INFO(node->get_logger(), "Added STL collision object to planning scene");

// parlight sensor add to end effector 

    // Load STL mesh for the sensor (1010-23-CL.stl)
  std::string sensor_stl_path = "file://" + package_path + "/meshes/1010-23-CL.stl";
  shapes::Mesh* sensor_mesh = shapes::createMeshFromResource(sensor_stl_path);

  if (!sensor_mesh) {
    RCLCPP_ERROR(node->get_logger(), "Failed to load sensor mesh from %s", sensor_stl_path.c_str());
    return 1;
  }

  // Scale sensor mesh (assuming it's in mm, like the previous one)
  double sensor_scale = 0.001;
  for (unsigned int i = 0; i < sensor_mesh->vertex_count; ++i) {
    sensor_mesh->vertices[3 * i + 0] *= sensor_scale;
    sensor_mesh->vertices[3 * i + 1] *= sensor_scale;
    sensor_mesh->vertices[3 * i + 2] *= sensor_scale;
  }

  shape_msgs::msg::Mesh sensor_mesh_msg;
  shapes::ShapeMsg sensor_mesh_msg_tmp;
  shapes::constructMsgFromShape(sensor_mesh, sensor_mesh_msg_tmp);
  sensor_mesh_msg = boost::get<shape_msgs::msg::Mesh>(sensor_mesh_msg_tmp);

  // Create the CollisionObject for the sensor mesh
  moveit_msgs::msg::CollisionObject sensor_object;
  sensor_object.header.frame_id = move_group.getEndEffectorLink();
  sensor_object.id = "sensor_mesh";

  sensor_object.meshes.push_back(sensor_mesh_msg);

  // Set pose relative to end effector
  geometry_msgs::msg::Pose sensor_pose;
  sensor_pose.orientation.x = 0.707;
  sensor_pose.orientation.y = 0.0;
  sensor_pose.orientation.z = 0.0;
  sensor_pose.orientation.w = 0.707;

  sensor_pose.position.x = (0)*0.0254;  // seems to be in y direction 
  sensor_pose.position.y =(-28) * 0.0254; // seems to be in x direction
  sensor_pose.position.z = (1) * 0.0254;

  sensor_object.mesh_poses.push_back(sensor_pose);
  sensor_object.operation = sensor_object.ADD;

  // Add and attach the object
  planning_scene_interface.applyCollisionObjects({sensor_object});
  //std::vector<std::string> touch_links = move_group.getLinkNames();
  //move_group.attachObject(sensor_object.id, move_group.getEndEffectorLink(), touch_links);
  std::vector<std::string> touch_links = {move_group.getEndEffectorLink()};
  move_group.attachObject(sensor_object.id, move_group.getEndEffectorLink(), touch_links);

  RCLCPP_INFO(node->get_logger(), "Attached mesh to the end effector.");


  // Wait briefly to ensure the object has been added to the scene
  rclcpp::sleep_for(std::chrono::seconds(1));

  RCLCPP_INFO(node->get_logger(), "Attached box to the end effector.");



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

  double z = -7*0.0254;

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
    rclcpp::sleep_for(std::chrono::seconds(1));

  } 
  else {
    RCLCPP_ERROR(node->get_logger(), "Planning failed!");
  }

  // Shutdown
  rclcpp::shutdown();
  return 0;
}