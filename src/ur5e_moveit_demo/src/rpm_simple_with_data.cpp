#include <memory>
#include <random>
#include <chrono>
#include <thread>
#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <tf2/LinearMath/Quaternion.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <fstream>
#include <filesystem>
#include <ament_index_cpp/get_package_share_directory.hpp>
// ----------------------------
// Generate random pose with uniform orientation (Shoemake method)
// ----------------------------
geometry_msgs::msg::Pose generateRandomPose(
    std::mt19937& rng,
    double min_x, double max_x,
    double min_y, double max_y,
    double min_z, double max_z)
{
    geometry_msgs::msg::Pose pose;

    std::uniform_real_distribution<double> dist_x(min_x, max_x);
    std::uniform_real_distribution<double> dist_y(min_y, max_y);
    std::uniform_real_distribution<double> dist_z(min_z, max_z);

    pose.position.x = dist_x(rng);
    pose.position.y = dist_y(rng);
    pose.position.z = dist_z(rng);

    // Shoemake uniform quaternion
    std::uniform_real_distribution<double> dist_u(0.0, 1.0);
    double u1 = dist_u(rng);
    double u2 = dist_u(rng);
    double u3 = dist_u(rng);

    double sqrt1_u1 = std::sqrt(1.0 - u1);
    double sqrt_u1 = std::sqrt(u1);
    double two_pi_u2 = 2.0 * M_PI * u2;
    double two_pi_u3 = 2.0 * M_PI * u3;

    tf2::Quaternion q(
        sqrt1_u1 * std::sin(two_pi_u2),
        sqrt1_u1 * std::cos(two_pi_u2),
        sqrt_u1 * std::sin(two_pi_u3),
        sqrt_u1 * std::cos(two_pi_u3)
    );
    q.normalize();

    pose.orientation = tf2::toMsg(q);

    return pose;
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("random_positioning_node_with_data");

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);

    std::filesystem::path data_dir = "/home/russell/ROS2_REPAS/src/ur5e_moveit_demo/rpm_data";

// Create the folder if it doesn't exist
    if (!std::filesystem::exists(data_dir)) {
        std::filesystem::create_directory(data_dir);
    }

// Build the full file path
    std::filesystem::path file_path = data_dir / "rotated_vectors.csv";

    std::ofstream logfile(file_path);
    if (!logfile.is_open()) {
        RCLCPP_ERROR(node->get_logger(), "Failed to open logfile!");
        return 1;
    }
    logfile << "rot_x,rot_y,rot_z,running_mean_x,running_mean_y,running_mean_z\n";

    // ----------------------------
    // Declare parameters
    // ----------------------------
    node->declare_parameter("workspace_min_x", 0.2);
    node->declare_parameter("workspace_max_x", 0.8);
    node->declare_parameter("workspace_min_y", -0.5);
    node->declare_parameter("workspace_max_y", 0.5);
    node->declare_parameter("workspace_min_z", 0.2);
    node->declare_parameter("workspace_max_z", 0.8);
    node->declare_parameter("planning_time", 5.0);
    node->declare_parameter("max_velocity_scaling", 0.3);
    node->declare_parameter("max_acceleration_scaling", 0.3);

    double workspace_min_x = node->get_parameter("workspace_min_x").as_double();
    double workspace_max_x = node->get_parameter("workspace_max_x").as_double();
    double workspace_min_y = node->get_parameter("workspace_min_y").as_double();
    double workspace_max_y = node->get_parameter("workspace_max_y").as_double();
    double workspace_min_z = node->get_parameter("workspace_min_z").as_double();
    double workspace_max_z = node->get_parameter("workspace_max_z").as_double();
    double planning_time = node->get_parameter("planning_time").as_double();
    double max_vel_scaling = node->get_parameter("max_velocity_scaling").as_double();
    double max_acc_scaling = node->get_parameter("max_acceleration_scaling").as_double();

    RCLCPP_INFO(node->get_logger(), "Random Positioning Node initialized");

    std::thread spin_thread([node]() { rclcpp::spin(node); });

    // ----------------------------
    // Initialize MoveIt
    // ----------------------------
    auto move_group = std::make_shared<moveit::planning_interface::MoveGroupInterface>(node, "ur_manipulator");
    move_group->setPlanningTime(planning_time);
    move_group->setMaxVelocityScalingFactor(max_vel_scaling);
    move_group->setMaxAccelerationScalingFactor(max_acc_scaling);

    // ----------------------------
    // Initialize PlanningSceneMonitor
    // ----------------------------

    RCLCPP_INFO(node->get_logger(), "MoveIt and PlanningSceneMonitor initialized. Starting random motion loop...");

    int success_count = 0;
    int attempt_count = 0;
    tf2::Vector3 running_sum(0.0, 0.0, 0.0);

    while (rclcpp::ok())
    {
        attempt_count++;
        geometry_msgs::msg::Pose target_pose = generateRandomPose(
            rng,
            workspace_min_x, workspace_max_x,
            workspace_min_y, workspace_max_y,
            workspace_min_z, workspace_max_z
        );

        RCLCPP_INFO(node->get_logger(),
                    "Attempt %d: Moving to position (%.3f, %.3f, %.3f)",
                    attempt_count,
                    target_pose.position.x,
                    target_pose.position.y,
                    target_pose.position.z);

        move_group->setPoseTarget(target_pose);

        moveit::planning_interface::MoveGroupInterface::Plan plan;
        bool success = (move_group->plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);

        if (success)
        {
            RCLCPP_INFO(node->get_logger(), "Plan found, executing...");
            move_group->execute(plan);
            success_count++;
            RCLCPP_INFO(node->get_logger(),
                        "Success rate: %d/%d (%.1f%%)",
                        success_count, attempt_count,
                        100.0 * success_count / attempt_count);
        }
        else
        {
            RCLCPP_WARN(node->get_logger(), "Planning failed, generating new target...");
        }

        // Rotate a fixed vector by the target orientation and track running mean
        tf2::Vector3 fixed_v(1.0, 0.0, 0.0);
        tf2::Quaternion q;
        tf2::fromMsg(target_pose.orientation, q);
        tf2::Vector3 rotated_v = tf2::quatRotate(q, fixed_v);

        running_sum += rotated_v;
        tf2::Vector3 running_mean = running_sum / attempt_count;

        logfile << std::fixed << std::setprecision(6)
                << rotated_v.x() << ","
                << rotated_v.y() << ","
                << rotated_v.z() << ","
                << running_mean.x() << ","
                << running_mean.y() << ","
                << running_mean.z() << "\n";

        logfile.flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    logfile.close();
    spin_thread.join();
    rclcpp::shutdown();
    return 0;
}
