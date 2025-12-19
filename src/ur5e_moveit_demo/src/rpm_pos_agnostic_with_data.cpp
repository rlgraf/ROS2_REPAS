#include <memory>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>
#include <iomanip>

#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/msg/collision_object.hpp>
#include <shape_msgs/msg/solid_primitive.hpp>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <geometry_msgs/msg/pose.hpp>

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("rpm_orientation_only_node");

    // -------------------------------
    // MoveIt interfaces
    // -------------------------------
    auto move_group =
        std::make_shared<moveit::planning_interface::MoveGroupInterface>(
            node, "ur_manipulator");

    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

    move_group->setGoalOrientationTolerance(0.01);
    move_group->setGoalPositionTolerance(1.0);

    // -------------------------------
    // ADD FORBIDDEN REGION (virtual floor)
    // -------------------------------
    moveit_msgs::msg::CollisionObject floor;
    floor.id = "forbidden_floor";
    floor.header.frame_id = "world";

    shape_msgs::msg::SolidPrimitive box;
    box.type = box.BOX;
    box.dimensions = {3.0, 3.0, 0.5};  // x, y, z

    geometry_msgs::msg::Pose floor_pose;
    floor_pose.orientation.w = 1.0;
    floor_pose.position.x = 0.0;
    floor_pose.position.y = 0.0;
    floor_pose.position.z = 0.09 - 0.25;  // top at 0.09m

    floor.primitives.push_back(box);
    floor.primitive_poses.push_back(floor_pose);
    floor.operation = floor.ADD;

    planning_scene_interface.applyCollisionObject(floor);
    RCLCPP_INFO(node->get_logger(), "Added forbidden region: z < 0.09 m");

    // -------------------------------
    // RNG setup
    // -------------------------------
    unsigned seed =
        std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist_u(0.0, 1.0);

    // -------------------------------
    // Data logging
    // -------------------------------
    std::filesystem::path data_dir =
        "/home/russell/ROS2_REPAS/src/ur5e_moveit_demo/rpm_data";
    std::filesystem::create_directories(data_dir);

    std::ofstream logfile(
        data_dir / "orientation_statistics_1.csv");
    logfile << "iter,rot_x,rot_y,rot_z,rot_w,"
            << "mean_x,mean_y,mean_z,mean_w,"
            << "roll,pitch,yaw,"
            << "mean_roll,mean_pitch,mean_yaw\n";

    // -------------------------------
    // Runtime variables
    // -------------------------------
    int success_count = 0;
    int attempt_count = 0;
    tf2::Vector3 running_sum(0, 0, 0);
    double running_sum_w = 0.0;

    double running_roll = 0.0;
    double running_pitch = 0.0;
    double running_yaw = 0.0;

    std::thread spin_thread([node]() { rclcpp::spin(node); });

    RCLCPP_INFO(node->get_logger(),
        "Orientation-only node started with forbidden region active");

    while (rclcpp::ok())
    {
        attempt_count++;

        // Generate random quaternion (Shoemake)
        double u1 = dist_u(rng), u2 = dist_u(rng), u3 = dist_u(rng);
        tf2::Quaternion q(
            std::sqrt(1 - u1) * std::sin(2 * M_PI * u2),
            std::sqrt(1 - u1) * std::cos(2 * M_PI * u2),
            std::sqrt(u1)     * std::sin(2 * M_PI * u3),
            std::sqrt(u1)     * std::cos(2 * M_PI * u3)
        );
        q.normalize();

        move_group->setOrientationTarget(
            q.x(), q.y(), q.z(), q.w(),
            move_group->getEndEffectorLink());

        moveit::planning_interface::MoveGroupInterface::Plan plan;
        bool success =
            move_group->plan(plan) == moveit::core::MoveItErrorCode::SUCCESS;

        if (success)
        {
            move_group->execute(plan);
            success_count++;

            tf2::Vector3 rotated = tf2::quatRotate(q, tf2::Vector3(1, 0, 0));
            double rotated_w = q.w();

            running_sum += rotated;
            running_sum_w += rotated_w;

            tf2::Vector3 mean = running_sum / success_count;
            double mean_w = running_sum_w / success_count;

            // Convert to roll, pitch, yaw
            double roll, pitch, yaw;
            tf2::Matrix3x3(q).getRPY(roll, pitch, yaw);

            // Update running sum of angles
            running_roll += roll;
            running_pitch += pitch;
            running_yaw += yaw;

            double mean_roll = running_roll / success_count;
            double mean_pitch = running_pitch / success_count;
            double mean_yaw = running_yaw / success_count;

            logfile << success_count << ","
                    << rotated.x() << "," << rotated.y() << "," << rotated.z() << "," << rotated_w << ","
                    << mean.x() << "," << mean.y() << "," << mean.z() << "," << mean_w << ","
                    << roll << "," << pitch << "," << yaw << ","
                    << mean_roll << "," << mean_pitch << "," << mean_yaw << "\n";

            logfile.flush();

            RCLCPP_INFO(node->get_logger(),
                "Success %d/%d (%.1f%%)",
                success_count, attempt_count,
                100.0 * success_count / attempt_count);
        }
        else
        {
            RCLCPP_WARN(node->get_logger(),
                "Planning rejected (likely floor constraint) — not logged");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    logfile.close();
    spin_thread.join();
    rclcpp::shutdown();
    return 0;
}
