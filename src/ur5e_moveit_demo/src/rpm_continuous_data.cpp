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

// Success rate
int total_attempts = 0;
int successful_executions = 0;

// ------------------------- Acceleration history -------------------------
bool has_prev_pose = false;
bool has_prev_vel = false;
bool has_prev_q = false;
bool has_prev_omega = false;

tf2::Vector3 prev_position(0, 0, 0);
tf2::Vector3 prev_linear_velocity(0, 0, 0);

tf2::Quaternion prev_q;
tf2::Vector3 prev_angular_velocity(0, 0, 0);

rclcpp::Time prev_time;

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

    geometry_msgs::msg::Pose pose;
    pose.orientation.w = 1.0;
    pose.position.z = 0.09 - 0.25;

    floor.primitives.push_back(box);
    floor.primitive_poses.push_back(pose);
    floor.operation = floor.ADD;

    planning_scene.applyCollisionObject(floor);
}

// ------------------------- Log orientation + acceleration -------------------------
void logCurrentOrientation(std::ofstream &logfile,
                           moveit::core::RobotStatePtr kinematic_state,
                           const moveit::planning_interface::MoveGroupInterface &move_group)
{
    if (!last_joint_state)
        return;

    // ---------------- FK ----------------
    for (size_t i = 0; i < last_joint_state->name.size(); ++i)
        kinematic_state->setJointPositions(
            last_joint_state->name[i],
            &last_joint_state->position[i]);

    const std::string ee_link = move_group.getEndEffectorLink();
    auto tf = kinematic_state->getGlobalLinkTransform(ee_link);

    // ---------------- Orientation ----------------
    Eigen::Matrix3d R = tf.rotation();
    tf2::Matrix3x3 tf2_R(
        R(0,0), R(0,1), R(0,2),
        R(1,0), R(1,1), R(1,2),
        R(2,0), R(2,1), R(2,2));

    tf2::Quaternion q;
    tf2_R.getRotation(q);
    q.normalize();

    tf2::Vector3 rotated = tf2::quatRotate(q, tf2::Vector3(1, 0, 0));

    double roll, pitch, yaw;
    tf2::Matrix3x3(q).getRPY(roll, pitch, yaw);

    // ---------------- Running means ----------------
    sample_count++;
    running_sum += rotated;
    running_sum_w += q.w();
    running_roll += roll;
    running_pitch += pitch;
    running_yaw += yaw;

    tf2::Vector3 mean = running_sum / sample_count;

    // ---------------- Position ----------------
    Eigen::Vector3d p = tf.translation();
    tf2::Vector3 position(p.x(), p.y(), p.z());

    rclcpp::Time now = rclcpp::Clock().now();

    // ---------------- Linear acceleration ----------------
    tf2::Vector3 linear_velocity(0, 0, 0);
    tf2::Vector3 linear_acceleration(0, 0, 0);

    // ---------------- Angular acceleration ----------------
    tf2::Vector3 angular_velocity(0, 0, 0);
    tf2::Vector3 angular_acceleration(0, 0, 0);

    if (has_prev_pose)
    {
        double dt = (now - prev_time).seconds();
        if (dt > 1e-6)
        {
            linear_velocity = (position - prev_position) / dt;

            if (has_prev_vel)
                linear_acceleration =
                    (linear_velocity - prev_linear_velocity) / dt;

            tf2::Quaternion dq = q * prev_q.inverse();
            dq.normalize();

            if (dq.getAngle() < M_PI)
                angular_velocity =
                    dq.getAxis() * (dq.getAngle() / dt);

            if (has_prev_omega)
                angular_acceleration =
                    (angular_velocity - prev_angular_velocity) / dt;

            prev_linear_velocity = linear_velocity;
            prev_angular_velocity = angular_velocity;
            has_prev_vel = true;
            has_prev_omega = true;
        }
    }

    prev_position = position;
    prev_q = q;
    prev_time = now;
    has_prev_pose = true;
    has_prev_q = true;

    double a_mag = linear_acceleration.length();
    double alpha_mag = angular_acceleration.length();

    // ---------------- Success rate ----------------
    double success_rate =
        total_attempts > 0
            ? double(successful_executions) / total_attempts
            : 0.0;

    // ---------------- CSV ----------------
    logfile << sample_count << ","
            << rotated.x() << "," << rotated.y() << "," << rotated.z() << "," << q.w() << ","
            << mean.x() << "," << mean.y() << "," << mean.z() << "," << (running_sum_w / sample_count) << ","
            << roll << "," << pitch << "," << yaw << ","
            << (running_roll / sample_count) << ","
            << (running_pitch / sample_count) << ","
            << (running_yaw / sample_count) << ","
            << linear_acceleration.x() << ","
            << linear_acceleration.y() << ","
            << linear_acceleration.z() << ","
            << a_mag << ","
            << angular_acceleration.x() << ","
            << angular_acceleration.y() << ","
            << angular_acceleration.z() << ","
            << alpha_mag << ","
            << success_rate
            << "\n";

    logfile.flush();
}

// ------------------------- Main -------------------------
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("rpm_orientation_node");

    auto move_group =
        std::make_shared<moveit::planning_interface::MoveGroupInterface>(
            node, "ur_manipulator");

    moveit::planning_interface::PlanningSceneInterface planning_scene;
    addForbiddenFloor(planning_scene);

    robot_model_loader::RobotModelLoader loader(node, "robot_description");
    auto model = loader.getModel();
    auto state = std::make_shared<moveit::core::RobotState>(model);
    state->setToDefaultValues();

    auto joint_sub = node->create_subscription<sensor_msgs::msg::JointState>(
        "/joint_states", 10, jointStateCallback);

    // ---------------- Velocity & Acceleration Scaling ----------------
    move_group->setMaxVelocityScalingFactor(0.025);      // 2.5% of max joint velocity
    move_group->setMaxAccelerationScalingFactor(0.0125); // 1.25% of max joint acceleration

    std::filesystem::path dir =
        "/home/russell/ROS2_REPAS/src/ur5e_moveit_demo/rpm_data";
    std::filesystem::create_directories(dir);

    std::ofstream logfile(dir / "orientation_stats_with_accel.csv");
    logfile <<
        "iter,"
        "rot_x,rot_y,rot_z,rot_w,"
        "mean_x,mean_y,mean_z,mean_w,"
        "roll,pitch,yaw,"
        "mean_roll,mean_pitch,mean_yaw,"
        "a_x,a_y,a_z,a_mag,"
        "alpha_x,alpha_y,alpha_z,alpha_mag,"
        "success_rate\n";

    logfile << std::fixed << std::setprecision(6);

    auto timer = node->create_wall_timer(
        std::chrono::seconds(1),
        [&]() { logCurrentOrientation(logfile, state, *move_group); });

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> U(0.0, 1.0);

    std::thread planner([&]() {
        while (rclcpp::ok())
        {
            double u1 = U(rng), u2 = U(rng), u3 = U(rng);
            tf2::Quaternion q(
                std::sqrt(1-u1)*std::sin(2*M_PI*u2),
                std::sqrt(1-u1)*std::cos(2*M_PI*u2),
                std::sqrt(u1)*std::sin(2*M_PI*u3),
                std::sqrt(u1)*std::cos(2*M_PI*u3));

            move_group->setOrientationTarget(
                q.x(), q.y(), q.z(), q.w(),
                move_group->getEndEffectorLink());

            total_attempts++;
            moveit::planning_interface::MoveGroupInterface::Plan plan;
            if (move_group->plan(plan) ==
                moveit::core::MoveItErrorCode::SUCCESS)
            {
                move_group->asyncExecute(plan);
                successful_executions++;
            }

            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    });

    rclcpp::spin(node);

    planner.join();
    logfile.close();
    rclcpp::shutdown();
    return 0;
}
