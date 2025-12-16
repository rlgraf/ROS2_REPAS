#include <memory>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>
#include <iomanip>

#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <tf2/LinearMath/Quaternion.h>

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("rpm_orientation_only_node");

    // Seed random number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist_u(0.0, 1.0);

    // Data directory
    std::filesystem::path data_dir = "/home/russell/ROS2_REPAS/src/ur5e_moveit_demo/rpm_data";
    if (!std::filesystem::exists(data_dir))
        std::filesystem::create_directory(data_dir);

    std::filesystem::path file_path = data_dir / "rotated_vectors_orientation_only.csv";
    std::ofstream logfile(file_path);
    if (!logfile.is_open()) {
        RCLCPP_ERROR(node->get_logger(), "Failed to open logfile!");
        return 1;
    }
    logfile << "rot_x,rot_y,rot_z,running_mean_x,running_mean_y,running_mean_z\n";

    // Initialize MoveGroup
    auto move_group = std::make_shared<moveit::planning_interface::MoveGroupInterface>(node, "ur_manipulator");

    move_group->setGoalOrientationTolerance(0.01); // tight orientation tolerance
    move_group->setGoalPositionTolerance(1.0);     // very loose position tolerance

    RCLCPP_INFO(node->get_logger(), "Orientation-only node started");

    int success_count = 0;
    int attempt_count = 0;
    tf2::Vector3 running_sum(0.0, 0.0, 0.0);

    std::thread spin_thread([node]() { rclcpp::spin(node); });

    while (rclcpp::ok())
    {
        attempt_count++;

        // Generate a random quaternion using Shoemake method
        double u1 = dist_u(rng), u2 = dist_u(rng), u3 = dist_u(rng);
        double sqrt1_u1 = std::sqrt(1.0 - u1);
        double sqrt_u1  = std::sqrt(u1);
        double two_pi_u2 = 2.0 * M_PI * u2;
        double two_pi_u3 = 2.0 * M_PI * u3;

        tf2::Quaternion q(
            sqrt1_u1 * std::sin(two_pi_u2),
            sqrt1_u1 * std::cos(two_pi_u2),
            sqrt_u1  * std::sin(two_pi_u3),
            sqrt_u1  * std::cos(two_pi_u3)
        );
        q.normalize();

        // Manually convert tf2::Quaternion to geometry_msgs::msg::Quaternion
        geometry_msgs::msg::Quaternion q_msg;
        q_msg.x = q.x();
        q_msg.y = q.y();
        q_msg.z = q.z();
        q_msg.w = q.w();

        // Set orientation target (pass x,y,z,w separately for ROS 2 Jazzy)
        move_group->setOrientationTarget(
            q_msg.x,
            q_msg.y,
            q_msg.z,
            q_msg.w,
            move_group->getEndEffectorLink()
        );

        moveit::planning_interface::MoveGroupInterface::Plan plan;
        bool success = (move_group->plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);

        if (success)
        {
            RCLCPP_INFO(node->get_logger(), "Plan found, executing orientation-only motion...");
            move_group->execute(plan);
            success_count++;

            // Fixed vector along x
            tf2::Vector3 fixed_v(1.0, 0.0, 0.0);
            tf2::Vector3 rotated_v = tf2::quatRotate(q, fixed_v);

            running_sum += rotated_v;
            tf2::Vector3 running_mean = running_sum / success_count;

            logfile << std::fixed << std::setprecision(6)
                    << rotated_v.x() << ","
                    << rotated_v.y() << ","
                    << rotated_v.z() << ","
                    << running_mean.x() << ","
                    << running_mean.y() << ","
                    << running_mean.z() << "\n";
            logfile.flush();

            RCLCPP_INFO(node->get_logger(),
                        "Success rate: %d/%d (%.1f%%)",
                        success_count, attempt_count,
                        100.0 * success_count / attempt_count);
        }
        else
        {
            RCLCPP_WARN(node->get_logger(), "Planning failed for sampled orientation, retrying...");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    logfile.close();
    spin_thread.join();
    rclcpp::shutdown();
    return 0;
}
