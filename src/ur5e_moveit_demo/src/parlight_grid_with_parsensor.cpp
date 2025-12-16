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
#include <std_msgs/msg/float32.hpp>
#include <memory>
#include <atomic>

#include <ament_index_cpp/get_package_share_directory.hpp>
#include <geometric_shapes/shape_operations.h>

std::atomic<double> g_camera_z_value = 0.0;


int main(int argc, char** argv)
{
  // Initialize ROS 2
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("parlight_grid_with_parsensor");


  auto subscription = node->create_subscription<std_msgs::msg::Float32>(
    "camera_return_z",  // must match your Python topic name
    10,
    [](const std_msgs::msg::Float32::SharedPtr msg) {
        g_camera_z_value.store(msg->data);
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Received camera z value: %.3f", msg->data);
    });

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

  mesh_pose.position.x = -0.037 - (32)*0.0254; // set appropriately
  mesh_pose.position.y = 0.048 + (12.875 - 5.5)*0.0254;
  mesh_pose.position.z = 0.0 - (2.75)*0.0254;

  collision_object.mesh_poses.push_back(mesh_pose);
  collision_object.operation = collision_object.ADD;

// Add the object to the planning scene
  planning_scene_interface.applyCollisionObjects({collision_object});
  RCLCPP_INFO(node->get_logger(), "Added STL collision object to planning scene");

// parlight sensor add to end effector 

  moveit_msgs::msg::CollisionObject sensor_rod;
  sensor_rod.header.frame_id = move_group.getEndEffectorLink();  // Attach to end effector
  sensor_rod.id = "sensor_rod";

// Define the box size
  shape_msgs::msg::SolidPrimitive sensor_rod_primitive;
  sensor_rod_primitive.type = shape_msgs::msg::SolidPrimitive::BOX;
  sensor_rod_primitive.dimensions = {(1)*0.0254, (25.375)*0.0254, (1.25)*0.0254}; // Width, Depth, Height in meters

// Define the pose relative to the end effector
  geometry_msgs::msg::Pose sensor_rod_pose;
  sensor_rod_pose.orientation.w = 1.0;  // No rotation
  sensor_rod_pose.position.x = 0.0;
  sensor_rod_pose.position.y = (13.4375)*0.0254;
  sensor_rod_pose.position.z = (1.625)*0.0254;  // Offset in Z (e.g., top of gripper)

  sensor_rod.primitives.push_back(sensor_rod_primitive);
  sensor_rod.primitive_poses.push_back(sensor_rod_pose);
  sensor_rod.operation = sensor_rod.ADD;

// Apply to the planning scene
  planning_scene_interface.applyCollisionObjects({sensor_rod});
  std::vector<std::string> touch_links = move_group.getLinkNames();
  move_group.attachObject(sensor_rod.id, move_group.getEndEffectorLink(), touch_links);

  // Wait briefly to ensure the object has been added to the scene
  rclcpp::sleep_for(std::chrono::seconds(1));

  RCLCPP_INFO(node->get_logger(), "Attached sensor rod to the end effector.");

// sensor_plate add

  moveit_msgs::msg::CollisionObject sensor_plate;
  sensor_plate.header.frame_id = move_group.getEndEffectorLink();  // Attach to end effector
  sensor_plate.id = "sensor_plate";

// Define the box size
  shape_msgs::msg::SolidPrimitive sensor_plate_primitive;
  sensor_plate_primitive.type = shape_msgs::msg::SolidPrimitive::BOX;
  sensor_plate_primitive.dimensions = {(6.25)*0.0254, (12)*0.0254, (0.5)*0.0254}; // Width, Depth, Height in meters

// Define the pose relative to the end effector
  geometry_msgs::msg::Pose sensor_plate_pose;
  sensor_plate_pose.orientation.w = 1.0;  // No rotation
  sensor_plate_pose.position.x = 0.0;
  sensor_plate_pose.position.y = (3.25)*0.0254;
  sensor_plate_pose.position.z = (0.75)*0.0254;  // Offset in Z (e.g., top of gripper)

  sensor_plate.primitives.push_back(sensor_plate_primitive);
  sensor_plate.primitive_poses.push_back(sensor_plate_pose);
  sensor_plate.operation = sensor_plate.ADD;

// Apply to the planning scene
  planning_scene_interface.applyCollisionObjects({sensor_plate});
  //std::vector<std::string> touch_links = move_group.getLinkNames();
  move_group.attachObject(sensor_plate.id, move_group.getEndEffectorLink(), touch_links);

  // Wait briefly to ensure the object has been added to the scene
  rclcpp::sleep_for(std::chrono::seconds(1));

  RCLCPP_INFO(node->get_logger(), "Attached sensor plate to the end effector.");

  // sensor_cylinder add

  moveit_msgs::msg::CollisionObject sensor_cylinder;
  sensor_cylinder.header.frame_id = move_group.getEndEffectorLink();  // Attach to end effector
  sensor_cylinder.id = "sensor_cylinder";

// Define the cylinder size
  shape_msgs::msg::SolidPrimitive cylinder_primitive;
  cylinder_primitive.type = shape_msgs::msg::SolidPrimitive::CYLINDER;
  cylinder_primitive.dimensions.resize(2);
  cylinder_primitive.dimensions[shape_msgs::msg::SolidPrimitive::CYLINDER_HEIGHT] = 1.25 * 0.0254; // Height in meters
  cylinder_primitive.dimensions[shape_msgs::msg::SolidPrimitive::CYLINDER_RADIUS] = 1.0 * 0.0254;  // Radius in meters

// Define the pose relative to the end effector
  geometry_msgs::msg::Pose cylinder_pose;
  cylinder_pose.orientation.w = 1.0;  // No rotation
  cylinder_pose.position.x = 0.0;
  cylinder_pose.position.y = (27.125)*0.0254;
  cylinder_pose.position.z = (1.625)*0.0254;; // Position to place base on EE, center of cylinder at half-height

  sensor_cylinder.primitives.push_back(cylinder_primitive);
  sensor_cylinder.primitive_poses.push_back(cylinder_pose);
  sensor_cylinder.operation = sensor_cylinder.ADD;

// Apply to the planning scene
  planning_scene_interface.applyCollisionObjects({sensor_cylinder});

// Optional: touch links if needed
// std::vector<std::string> touch_links = move_group.getLinkNames();
  move_group.attachObject(sensor_cylinder.id, move_group.getEndEffectorLink(), touch_links);

// Wait briefly to ensure the object has been added to the scene
  rclcpp::sleep_for(std::chrono::seconds(1));

  RCLCPP_INFO(node->get_logger(), "Attached sensor cylinder to the end effector.");


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
  RCLCPP_INFO(node->get_logger(), "Start EE Pose: x=%.4f, y=%.4f, z=%.4f",
            start_pose.position.x,
            start_pose.position.y,
            start_pose.position.z);

  start_pose.orientation.x;
  start_pose.orientation.y;
  start_pose.orientation.z;
  start_pose.orientation.w;
  start_pose.position.x;
  start_pose.position.y;
  start_pose.position.z;

  // SET HEIGHT

  //double z = -5*0.0254;
  double z = g_camera_z_value.load()* 0.0254;
  //double z_raw = g_camera_z_value.load()* 0.0254;
  //double z_to_canopy = -((9.5)*0.0254 + z_raw);
  //double z = z_to_canopy + 0.0; // 0.0 cm buffer to not hit plants
  
  //double z = -((12 - 3.5)* 0.0254 - (-z_raw) + 0.01);
  RCLCPP_INFO(node->get_logger(), "Using camera z value (in inches): %.3f", g_camera_z_value.load());


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
  //Node NA = {-8, 14};
  //Node NB = {0, 14};
 // Node NC = {8, 14};

  Node N1 = {-8, 10};
  Node N2 = {0, 10};
  Node N3 = {8, 10};
  Node N4 = {8, 4};
  Node N5 = {0, 4};
  Node N6 = {-8, 4};
  Node N7 = {-8, -4};
  Node N8 = {0, -4};
  Node N9 = {8, -4};
  Node N10 = {8, -10};
  Node N11 = {0, -10};
  Node N12 = {-8, -10};

  //Node N1 = {10, 0};
  //Node N2 = {10, 11.0};
  //Node N3 = {0, 11.0};
  //Node N4 = {-8, 11.0};
  //Node N5 = {10, 11.0};

  //Node N6 = {10, 0};
  //Node N7 = {10, -11.0};
  //Node N8 = {0, -11.0};
  //Node N9 = {-8, -11.0};
  //Node N10 = {10, -11.0};


  //std::vector<Node> nodes = {N1, N2, N3, N4, N5, N6, N7, N8, N9, N10, N11, N12};
  std::vector<Node> nodes = {N1, N2, N3, N4, N5, N6, N7, N8, N9, N10, N11, N12};


  for (size_t i = 0; i < nodes.size(); ++i) {
    double x_pos = nodes[i].x*0.0254;
    double y_pos = nodes[i].y*0.0254;

    geometry_msgs::msg::Pose current_pose = move_group.getCurrentPose().pose;
    
    geometry_msgs::msg::Pose target_pose = start_pose;
    target_pose.position.x += x_pos;
    target_pose.position.y += y_pos;
    std::vector<geometry_msgs::msg::Pose> waypoints;
 
    for (int j = 0; j < 40; j++){
      geometry_msgs::msg::Pose waypoint = current_pose;
      waypoint.position.x += (target_pose.position.x - current_pose.position.x) * (j / 40.0);
      waypoint.position.y += (target_pose.position.y - current_pose.position.y) * (j / 40.0);
      waypoint.orientation = start_pose.orientation;  // Fix orientation

      waypoints.push_back(waypoint);
    }
    moveit_msgs::msg::RobotTrajectory trajectory_approach;
    const double jump_threshold = 0.0;
    const double eef_step = 0.005;

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