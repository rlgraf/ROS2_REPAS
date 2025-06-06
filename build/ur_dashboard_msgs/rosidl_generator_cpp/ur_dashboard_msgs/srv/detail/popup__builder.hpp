// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ur_dashboard_msgs:srv/Popup.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "ur_dashboard_msgs/srv/popup.hpp"


#ifndef UR_DASHBOARD_MSGS__SRV__DETAIL__POPUP__BUILDER_HPP_
#define UR_DASHBOARD_MSGS__SRV__DETAIL__POPUP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ur_dashboard_msgs/srv/detail/popup__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ur_dashboard_msgs
{

namespace srv
{

namespace builder
{

class Init_Popup_Request_message
{
public:
  Init_Popup_Request_message()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::ur_dashboard_msgs::srv::Popup_Request message(::ur_dashboard_msgs::srv::Popup_Request::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_dashboard_msgs::srv::Popup_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_dashboard_msgs::srv::Popup_Request>()
{
  return ur_dashboard_msgs::srv::builder::Init_Popup_Request_message();
}

}  // namespace ur_dashboard_msgs


namespace ur_dashboard_msgs
{

namespace srv
{

namespace builder
{

class Init_Popup_Response_success
{
public:
  explicit Init_Popup_Response_success(::ur_dashboard_msgs::srv::Popup_Response & msg)
  : msg_(msg)
  {}
  ::ur_dashboard_msgs::srv::Popup_Response success(::ur_dashboard_msgs::srv::Popup_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_dashboard_msgs::srv::Popup_Response msg_;
};

class Init_Popup_Response_answer
{
public:
  Init_Popup_Response_answer()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Popup_Response_success answer(::ur_dashboard_msgs::srv::Popup_Response::_answer_type arg)
  {
    msg_.answer = std::move(arg);
    return Init_Popup_Response_success(msg_);
  }

private:
  ::ur_dashboard_msgs::srv::Popup_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_dashboard_msgs::srv::Popup_Response>()
{
  return ur_dashboard_msgs::srv::builder::Init_Popup_Response_answer();
}

}  // namespace ur_dashboard_msgs


namespace ur_dashboard_msgs
{

namespace srv
{

namespace builder
{

class Init_Popup_Event_response
{
public:
  explicit Init_Popup_Event_response(::ur_dashboard_msgs::srv::Popup_Event & msg)
  : msg_(msg)
  {}
  ::ur_dashboard_msgs::srv::Popup_Event response(::ur_dashboard_msgs::srv::Popup_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_dashboard_msgs::srv::Popup_Event msg_;
};

class Init_Popup_Event_request
{
public:
  explicit Init_Popup_Event_request(::ur_dashboard_msgs::srv::Popup_Event & msg)
  : msg_(msg)
  {}
  Init_Popup_Event_response request(::ur_dashboard_msgs::srv::Popup_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_Popup_Event_response(msg_);
  }

private:
  ::ur_dashboard_msgs::srv::Popup_Event msg_;
};

class Init_Popup_Event_info
{
public:
  Init_Popup_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Popup_Event_request info(::ur_dashboard_msgs::srv::Popup_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Popup_Event_request(msg_);
  }

private:
  ::ur_dashboard_msgs::srv::Popup_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_dashboard_msgs::srv::Popup_Event>()
{
  return ur_dashboard_msgs::srv::builder::Init_Popup_Event_info();
}

}  // namespace ur_dashboard_msgs

#endif  // UR_DASHBOARD_MSGS__SRV__DETAIL__POPUP__BUILDER_HPP_
