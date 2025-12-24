#include <memory>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>
#include <iomanip>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/msg/collision_object.hpp>
#include <shape_msgs/msg/solid_primitive.hpp>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <geometry_msgs/msg/pose.hpp>

#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_model_loader/robot_model_loader.h>

// ------------------------- Globals -------------------------
sensor_msgs::msg::JointState::SharedPtr last_joint_state = nullptr;
int sample_count = 0;
tf2::Vector3 running_sum(0, 0, 0);
double running_sum_w = 0.0;
double running_roll = 0.0;
double running_pitch = 0.0;
double running_yaw = 0.0;

// For success rate
int total_attempts = 0;
int successful_executions = 0;

// ------------------------- Joint state callback -------------------------
void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg)
{
    last_joint_state = msg;
}

// ------------------------- Add forbidden floor -------------------------
void addForbiddenFloor(moveit::planning_interface::PlanningSceneInterface &planning_scene)
{
    moveit_msgs::msg::CollisionObject floor;
    floor.id = "forbidden_floor";
    floor.header.frame_id = "world";

    shape_msgs::msg::SolidPrimitive box;
    box.type = box.BOX;
    box.dimensions = {3.0, 3.0, 0.5};

    geometry_msgs::msg::Pose floor_pose;
    floor_pose.orientation.w = 1.0;
    floor_pose.position.x = 0.0;
    floor_pose.position.y = 0.0;
    floor_pose.position.z = 0.09 - 0.25;

    floor.primitives.push_back(box);
    floor.primitive_poses.push_back(floor_pose);
    floor.operation = floor.ADD;

    planning_scene.applyCollisionObject(floor);
    RCLCPP_INFO(rclcpp::get_logger("rpm_orientation_node"), "Added forbidden region: z < 0.09 m");
}

// ------------------------- Log current orientation -------------------------
void logCurrentOrientation(std::ofstream &logfile,
                           moveit::core::RobotStatePtr kinematic_state,
                           const moveit::planning_interface::MoveGroupInterface &move_group)
{
    if (!last_joint_state)
        return;

    // Update FK
    for (size_t i = 0; i < last_joint_state->name.size(); ++i)
    {
        kinematic_state->setJointPositions(last_joint_state->name[i], &last_joint_state->position[i]);
    }

    const std::string ee_link = move_group.getEndEffectorLink();
    auto ee_transform = kinematic_state->getGlobalLinkTransform(ee_link);
    Eigen::Matrix3d R = ee_transform.rotation();
    tf2::Matrix3x3 tf2_R(
        R(0,0), R(0,1), R(0,2),
        R(1,0), R(1,1), R(1,2),
        R(2,0), R(2,1), R(2,2)
    );
    tf2::Quaternion q;
    tf2_R.getRotation(q);
    q.normalize();

    tf2::Vector3 rotated = tf2::quatRotate(q, tf2::Vector3(1, 0, 0));

    double roll, pitch, yaw;
    tf2::Matrix3x3(q).getRPY(roll, pitch, yaw);

    sample_count++;
    running_sum += rotated;
    running_sum_w += q.w();
    running_roll += roll;
    running_pitch += pitch;
    running_yaw += yaw;

    tf2::Vector3 mean = running_sum / sample_count;

    double success_rate = total_attempts > 0 ? double(successful_executions) / total_attempts : 0.0;

    logfile << sample_count << ","
            << rotated.x() << "," << rotated.y() << "," << rotated.z() << "," << q.w() << ","
            << mean.x() << "," << mean.y() << "," << mean.z() << "," << (running_sum_w / sample_count) << ","
            << roll << "," << pitch << "," << yaw << ","
            << (running_roll / sample_count) << ","
            << (running_pitch / sample_count) << ","
            << (running_yaw / sample_count) << ","
            << success_rate
            << "\n";

    logfile.flush();
}

// ------------------------- Main -------------------------
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("rpm_orientation_node");

    // -------------------------
    // MoveIt setup
    // -------------------------
    auto move_group = std::make_shared<moveit::planning_interface::MoveGroupInterface>(node, "ur_manipulator");
    moveit::planning_interface::PlanningSceneInterface planning_scene;
    move_group->setGoalOrientationTolerance(0.01);
    move_group->setGoalPositionTolerance(1.0);

    // -------------------------
    // Robot model for FK
    // -------------------------
    robot_model_loader::RobotModelLoader robot_model_loader(node, "robot_description");
    moveit::core::RobotModelPtr kinematic_model = robot_model_loader.getModel();
    moveit::core::RobotStatePtr kinematic_state = std::make_shared<moveit::core::RobotState>(kinematic_model);
    kinematic_state->setToDefaultValues();

    // -------------------------
    // Joint state subscription
    // -------------------------
    auto joint_state_sub = node->create_subscription<sensor_msgs::msg::JointState>(
        "/joint_states", 10, jointStateCallback);

    // -------------------------
    // Add forbidden floor
    // -------------------------
    addForbiddenFloor(planning_scene);

    // -------------------------
    // RNG
    // -------------------------
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> dist_u(0.0, 1.0);

    // -------------------------
    // Log file
    // -------------------------
    std::filesystem::path data_dir = "/home/russell/ROS2_REPAS/src/ur5e_moveit_demo/rpm_data";
    std::filesystem::create_directories(data_dir);
    std::ofstream logfile(data_dir / "orientation_stats_const1s_2.csv");
    logfile << "iter,rot_x,rot_y,rot_z,rot_w,mean_x,mean_y,mean_z,mean_w,roll,pitch,yaw,mean_roll,mean_pitch,mean_yaw,success_rate\n";
    logfile << std::fixed << std::setprecision(6);

    // -------------------------
    // Timer for 1 Hz logging
    // -------------------------
    auto timer = node->create_wall_timer(
        std::chrono::seconds(1),
        [&]() { logCurrentOrientation(logfile, kinematic_state, *move_group); });

    // -------------------------
    // Planning loop (random orientations every 5 seconds)
    // -------------------------
    std::thread planning_thread([&]() {
        while (rclcpp::ok())
        {
            double u1 = dist_u(rng);
            double u2 = dist_u(rng);
            double u3 = dist_u(rng);

            tf2::Quaternion q(
                std::sqrt(1 - u1) * std::sin(2 * M_PI * u2),
                std::sqrt(1 - u1) * std::cos(2 * M_PI * u2),
                std::sqrt(u1) * std::sin(2 * M_PI * u3),
                std::sqrt(u1) * std::cos(2 * M_PI * u3));
            q.normalize();

            move_group->setOrientationTarget(q.x(), q.y(), q.z(), q.w(),
                                            move_group->getEndEffectorLink());

            total_attempts++;
            moveit::planning_interface::MoveGroupInterface::Plan plan;
            bool success = (move_group->plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);
            if (success)
            {
                move_group->asyncExecute(plan);
                successful_executions++;
                RCLCPP_INFO(node->get_logger(), "Executing new orientation");
            }
            else
            {
                RCLCPP_WARN(node->get_logger(), "Planning failed — robot holds pose");
            }

            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    });

    // -------------------------
    // Spin node
    // -------------------------
    rclcpp::spin(node);

    if (planning_thread.joinable())
        planning_thread.join();
    logfile.close();
    rclcpp::shutdown();
    return 0;
}
