// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robotiq_2f_gripper_msgs:action/MoveTwoFingerGripper.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robotiq_2f_gripper_msgs/action/move_two_finger_gripper.hpp"


#ifndef ROBOTIQ_2F_GRIPPER_MSGS__ACTION__DETAIL__MOVE_TWO_FINGER_GRIPPER__STRUCT_HPP_
#define ROBOTIQ_2F_GRIPPER_MSGS__ACTION__DETAIL__MOVE_TWO_FINGER_GRIPPER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Goal __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Goal __declspec(deprecated)
#endif

namespace robotiq_2f_gripper_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveTwoFingerGripper_Goal_
{
  using Type = MoveTwoFingerGripper_Goal_<ContainerAllocator>;

  explicit MoveTwoFingerGripper_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->target_speed = 1.0f;
      this->target_force = 0.5f;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->target_position = 0.0f;
      this->target_speed = 0.0f;
      this->target_force = 0.0f;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_position = 0.0f;
    }
  }

  explicit MoveTwoFingerGripper_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->target_speed = 1.0f;
      this->target_force = 0.5f;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->target_position = 0.0f;
      this->target_speed = 0.0f;
      this->target_force = 0.0f;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_position = 0.0f;
    }
  }

  // field types and members
  using _target_position_type =
    float;
  _target_position_type target_position;
  using _target_speed_type =
    float;
  _target_speed_type target_speed;
  using _target_force_type =
    float;
  _target_force_type target_force;

  // setters for named parameter idiom
  Type & set__target_position(
    const float & _arg)
  {
    this->target_position = _arg;
    return *this;
  }
  Type & set__target_speed(
    const float & _arg)
  {
    this->target_speed = _arg;
    return *this;
  }
  Type & set__target_force(
    const float & _arg)
  {
    this->target_force = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Goal
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Goal
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveTwoFingerGripper_Goal_ & other) const
  {
    if (this->target_position != other.target_position) {
      return false;
    }
    if (this->target_speed != other.target_speed) {
      return false;
    }
    if (this->target_force != other.target_force) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveTwoFingerGripper_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveTwoFingerGripper_Goal_

// alias to use template instance with default allocator
using MoveTwoFingerGripper_Goal =
  robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs


#ifndef _WIN32
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Result __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Result __declspec(deprecated)
#endif

namespace robotiq_2f_gripper_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveTwoFingerGripper_Result_
{
  using Type = MoveTwoFingerGripper_Result_<ContainerAllocator>;

  explicit MoveTwoFingerGripper_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  explicit MoveTwoFingerGripper_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Result
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Result
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveTwoFingerGripper_Result_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveTwoFingerGripper_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveTwoFingerGripper_Result_

// alias to use template instance with default allocator
using MoveTwoFingerGripper_Result =
  robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs


#ifndef _WIN32
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Feedback __declspec(deprecated)
#endif

namespace robotiq_2f_gripper_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveTwoFingerGripper_Feedback_
{
  using Type = MoveTwoFingerGripper_Feedback_<ContainerAllocator>;

  explicit MoveTwoFingerGripper_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->feedback = "";
    }
  }

  explicit MoveTwoFingerGripper_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : feedback(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->feedback = "";
    }
  }

  // field types and members
  using _feedback_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__feedback(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Feedback
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_Feedback
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveTwoFingerGripper_Feedback_ & other) const
  {
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveTwoFingerGripper_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveTwoFingerGripper_Feedback_

// alias to use template instance with default allocator
using MoveTwoFingerGripper_Feedback =
  robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "robotiq_2f_gripper_msgs/action/detail/move_two_finger_gripper__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Request __declspec(deprecated)
#endif

namespace robotiq_2f_gripper_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveTwoFingerGripper_SendGoal_Request_
{
  using Type = MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator>;

  explicit MoveTwoFingerGripper_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit MoveTwoFingerGripper_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Request
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Request
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveTwoFingerGripper_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveTwoFingerGripper_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveTwoFingerGripper_SendGoal_Request_

// alias to use template instance with default allocator
using MoveTwoFingerGripper_SendGoal_Request =
  robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Response __declspec(deprecated)
#endif

namespace robotiq_2f_gripper_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveTwoFingerGripper_SendGoal_Response_
{
  using Type = MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator>;

  explicit MoveTwoFingerGripper_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit MoveTwoFingerGripper_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Response
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Response
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveTwoFingerGripper_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveTwoFingerGripper_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveTwoFingerGripper_SendGoal_Response_

// alias to use template instance with default allocator
using MoveTwoFingerGripper_SendGoal_Response =
  robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Event __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Event __declspec(deprecated)
#endif

namespace robotiq_2f_gripper_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveTwoFingerGripper_SendGoal_Event_
{
  using Type = MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator>;

  explicit MoveTwoFingerGripper_SendGoal_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit MoveTwoFingerGripper_SendGoal_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Event
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_SendGoal_Event
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveTwoFingerGripper_SendGoal_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveTwoFingerGripper_SendGoal_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveTwoFingerGripper_SendGoal_Event_

// alias to use template instance with default allocator
using MoveTwoFingerGripper_SendGoal_Event =
  robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs

namespace robotiq_2f_gripper_msgs
{

namespace action
{

struct MoveTwoFingerGripper_SendGoal
{
  using Request = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Request;
  using Response = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Response;
  using Event = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal_Event;
};

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Request __declspec(deprecated)
#endif

namespace robotiq_2f_gripper_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveTwoFingerGripper_GetResult_Request_
{
  using Type = MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator>;

  explicit MoveTwoFingerGripper_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit MoveTwoFingerGripper_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Request
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Request
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveTwoFingerGripper_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveTwoFingerGripper_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveTwoFingerGripper_GetResult_Request_

// alias to use template instance with default allocator
using MoveTwoFingerGripper_GetResult_Request =
  robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs


// Include directives for member types
// Member 'result'
// already included above
// #include "robotiq_2f_gripper_msgs/action/detail/move_two_finger_gripper__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Response __declspec(deprecated)
#endif

namespace robotiq_2f_gripper_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveTwoFingerGripper_GetResult_Response_
{
  using Type = MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator>;

  explicit MoveTwoFingerGripper_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit MoveTwoFingerGripper_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Response
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Response
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveTwoFingerGripper_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveTwoFingerGripper_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveTwoFingerGripper_GetResult_Response_

// alias to use template instance with default allocator
using MoveTwoFingerGripper_GetResult_Response =
  robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs


// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Event __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Event __declspec(deprecated)
#endif

namespace robotiq_2f_gripper_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveTwoFingerGripper_GetResult_Event_
{
  using Type = MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator>;

  explicit MoveTwoFingerGripper_GetResult_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit MoveTwoFingerGripper_GetResult_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Event
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_GetResult_Event
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveTwoFingerGripper_GetResult_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveTwoFingerGripper_GetResult_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveTwoFingerGripper_GetResult_Event_

// alias to use template instance with default allocator
using MoveTwoFingerGripper_GetResult_Event =
  robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs

namespace robotiq_2f_gripper_msgs
{

namespace action
{

struct MoveTwoFingerGripper_GetResult
{
  using Request = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Request;
  using Response = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Response;
  using Event = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult_Event;
};

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "robotiq_2f_gripper_msgs/action/detail/move_two_finger_gripper__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_FeedbackMessage __declspec(deprecated)
#endif

namespace robotiq_2f_gripper_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveTwoFingerGripper_FeedbackMessage_
{
  using Type = MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator>;

  explicit MoveTwoFingerGripper_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit MoveTwoFingerGripper_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_FeedbackMessage
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_2f_gripper_msgs__action__MoveTwoFingerGripper_FeedbackMessage
    std::shared_ptr<robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveTwoFingerGripper_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveTwoFingerGripper_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveTwoFingerGripper_FeedbackMessage_

// alias to use template instance with default allocator
using MoveTwoFingerGripper_FeedbackMessage =
  robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace robotiq_2f_gripper_msgs
{

namespace action
{

struct MoveTwoFingerGripper
{
  /// The goal message defined in the action definition.
  using Goal = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Goal;
  /// The result message defined in the action definition.
  using Result = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Result;
  /// The feedback message defined in the action definition.
  using Feedback = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = robotiq_2f_gripper_msgs::action::MoveTwoFingerGripper_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct MoveTwoFingerGripper MoveTwoFingerGripper;

}  // namespace action

}  // namespace robotiq_2f_gripper_msgs

#endif  // ROBOTIQ_2F_GRIPPER_MSGS__ACTION__DETAIL__MOVE_TWO_FINGER_GRIPPER__STRUCT_HPP_
