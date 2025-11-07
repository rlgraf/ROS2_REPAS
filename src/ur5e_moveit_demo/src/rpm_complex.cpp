#include <memory>
#include <random>
#include <chrono>
#include <thread>
#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/planning_scene_monitor/planning_scene_monitor.h>
#include <geometry_msgs/msg/pose.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

// Generate a random pose with uniform orientation
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
    
    // Shoemake quaternion for uniform orientation
    std::uniform_real_distribution<double> dist_u(0.0, 1.0);
    double u1 = dist_u(rng), u2 = dist_u(rng), u3 = dist_u(rng);
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

// Approximate safe distance check: tool z > min_distance_from_lower_arm
bool isPoseSafe(const geometry_msgs::msg::Pose& pose, double min_distance_from_lower_arm, double workspace_min_z)
{
    return pose.position.z >= workspace_min_z + min_distance_from_lower_arm;
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("random_positioning_node");

    // Random generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);

    // Parameters
    node->declare_parameter("workspace_min_x", 0.2);
    node->declare_parameter("workspace_max_x", 0.8);
    node->declare_parameter("workspace_min_y", -0.5);
    node->declare_parameter("workspace_max_y", 0.5);
    node->declare_parameter("workspace_min_z", 0.2);
    node->declare_parameter("workspace_max_z", 0.8);
    node->declare_parameter("planning_time", 5.0);
    node->declare_parameter("max_velocity_scaling", 0.3);
    node->declare_parameter("max_acceleration_scaling", 0.3);
    node->declare_parameter("min_tool_distance_from_lower_arm", 0.028); // 2.8 cm

    double workspace_min_x = node->get_parameter("workspace_min_x").as_double();
    double workspace_max_x = node->get_parameter("workspace_max_x").as_double();
    double workspace_min_y = node->get_parameter("workspace_min_y").as_double();
    double workspace_max_y = node->get_parameter("workspace_max_y").as_double();
    double workspace_min_z = node->get_parameter("workspace_min_z").as_double();
    double workspace_max_z = node->get_parameter("workspace_max_z").as_double();
    double planning_time = node->get_parameter("planning_time").as_double();
    double max_vel_scaling = node->get_parameter("max_velocity_scaling").as_double();
    double max_acc_scaling = node->get_parameter("max_acceleration_scaling").as_double();
    double min_distance = node->get_parameter("min_tool_distance_from_lower_arm").as_double();

    RCLCPP_INFO(node->get_logger(), "Random Positioning Node initialized");

    // Spin node in background
    std::thread spin_thread([node]() { rclcpp::spin(node); });

    auto move_group = std::make_shared<moveit::planning_interface::MoveGroupInterface>(node, "ur_manipulator");
    move_group->setPlanningTime(planning_time);
    move_group->setMaxVelocityScalingFactor(max_vel_scaling);
    move_group->setMaxAccelerationScalingFactor(max_acc_scaling);

    // Set up PlanningSceneMonitor for self-collision checking
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    moveit::planning_scene_monitor::PlanningSceneMonitor psm(move_group->getRobotModel());
    psm.startSceneMonitor();
    psm.startStateMonitor();

    RCLCPP_INFO(node->get_logger(), "MoveIt initialized. Starting random motion loop...");

    int success_count = 0;
    int attempt_count = 0;

    while (rclcpp::ok())
    {
        attempt_count++;
        geometry_msgs::msg::Pose target_pose = generateRandomPose(
            rng, workspace_min_x, workspace_max_x,
            workspace_min_y, workspace_max_y,
            workspace_min_z, workspace_max_z
        );

        // Quick safety check for min tool distance
        if (!isPoseSafe(target_pose, min_distance, workspace_min_z))
        {
            RCLCPP_WARN(node->get_logger(), "Pose too close to lower arm, skipping...");
            continue;
        }

        RCLCPP_INFO(node->get_logger(),
            "Attempt %d: Moving to (%.3f, %.3f, %.3f)",
            attempt_count,
            target_pose.position.x,
            target_pose.position.y,
            target_pose.position.z);

        move_group->setPoseTarget(target_pose);

        moveit::planning_interface::MoveGroupInterface::Plan plan;
        bool success = (move_group->plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);

        // Check for collisions before executing
        if (success)
        {
            // Update planning scene for collision checking
            moveit::core::RobotStatePtr current_state = move_group->getCurrentState();
            if (!psm.getPlanningScene()->isStateColliding(*current_state, move_group->getName()))
            {
                RCLCPP_INFO(node->get_logger(), "Plan safe, executing...");
                move_group->execute(plan);
                success_count++;
                RCLCPP_INFO(node->get_logger(),
                    "Success rate: %d/%d (%.1f%%)",
                    success_count, attempt_count,
                    100.0 * success_count / attempt_count);
            }
            else
            {
                RCLCPP_WARN(node->get_logger(), "Self-collision detected, skipping...");
            }
        }
        else
        {
            RCLCPP_WARN(node->get_logger(), "Planning failed, skipping...");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    spin_thread.join();
    rclcpp::shutdown();
    return 0;
}
