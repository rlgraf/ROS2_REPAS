// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ur_dashboard_msgs:srv/Load.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ur_dashboard_msgs/srv/detail/load__rosidl_typesupport_introspection_c.h"
#include "ur_dashboard_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ur_dashboard_msgs/srv/detail/load__functions.h"
#include "ur_dashboard_msgs/srv/detail/load__struct.h"


// Include directives for member types
// Member `filename`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ur_dashboard_msgs__srv__Load_Request__init(message_memory);
}

void ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_fini_function(void * message_memory)
{
  ur_dashboard_msgs__srv__Load_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_message_member_array[1] = {
  {
    "filename",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ur_dashboard_msgs__srv__Load_Request, filename),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_message_members = {
  "ur_dashboard_msgs__srv",  // message namespace
  "Load_Request",  // message name
  1,  // number of fields
  sizeof(ur_dashboard_msgs__srv__Load_Request),
  false,  // has_any_key_member_
  ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_message_member_array,  // message members
  ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_message_type_support_handle = {
  0,
  &ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_message_members,
  get_message_typesupport_handle_function,
  &ur_dashboard_msgs__srv__Load_Request__get_type_hash,
  &ur_dashboard_msgs__srv__Load_Request__get_type_description,
  &ur_dashboard_msgs__srv__Load_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ur_dashboard_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load_Request)() {
  if (!ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_message_type_support_handle.typesupport_identifier) {
    ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "ur_dashboard_msgs/srv/detail/load__rosidl_typesupport_introspection_c.h"
// already included above
// #include "ur_dashboard_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "ur_dashboard_msgs/srv/detail/load__functions.h"
// already included above
// #include "ur_dashboard_msgs/srv/detail/load__struct.h"


// Include directives for member types
// Member `answer`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ur_dashboard_msgs__srv__Load_Response__init(message_memory);
}

void ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_fini_function(void * message_memory)
{
  ur_dashboard_msgs__srv__Load_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_message_member_array[2] = {
  {
    "answer",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ur_dashboard_msgs__srv__Load_Response, answer),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ur_dashboard_msgs__srv__Load_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_message_members = {
  "ur_dashboard_msgs__srv",  // message namespace
  "Load_Response",  // message name
  2,  // number of fields
  sizeof(ur_dashboard_msgs__srv__Load_Response),
  false,  // has_any_key_member_
  ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_message_member_array,  // message members
  ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_message_type_support_handle = {
  0,
  &ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_message_members,
  get_message_typesupport_handle_function,
  &ur_dashboard_msgs__srv__Load_Response__get_type_hash,
  &ur_dashboard_msgs__srv__Load_Response__get_type_description,
  &ur_dashboard_msgs__srv__Load_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ur_dashboard_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load_Response)() {
  if (!ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_message_type_support_handle.typesupport_identifier) {
    ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "ur_dashboard_msgs/srv/detail/load__rosidl_typesupport_introspection_c.h"
// already included above
// #include "ur_dashboard_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "ur_dashboard_msgs/srv/detail/load__functions.h"
// already included above
// #include "ur_dashboard_msgs/srv/detail/load__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "ur_dashboard_msgs/srv/load.h"
// Member `request`
// Member `response`
// already included above
// #include "ur_dashboard_msgs/srv/detail/load__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ur_dashboard_msgs__srv__Load_Event__init(message_memory);
}

void ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_fini_function(void * message_memory)
{
  ur_dashboard_msgs__srv__Load_Event__fini(message_memory);
}

size_t ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__size_function__Load_Event__request(
  const void * untyped_member)
{
  const ur_dashboard_msgs__srv__Load_Request__Sequence * member =
    (const ur_dashboard_msgs__srv__Load_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_const_function__Load_Event__request(
  const void * untyped_member, size_t index)
{
  const ur_dashboard_msgs__srv__Load_Request__Sequence * member =
    (const ur_dashboard_msgs__srv__Load_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_function__Load_Event__request(
  void * untyped_member, size_t index)
{
  ur_dashboard_msgs__srv__Load_Request__Sequence * member =
    (ur_dashboard_msgs__srv__Load_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__fetch_function__Load_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const ur_dashboard_msgs__srv__Load_Request * item =
    ((const ur_dashboard_msgs__srv__Load_Request *)
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_const_function__Load_Event__request(untyped_member, index));
  ur_dashboard_msgs__srv__Load_Request * value =
    (ur_dashboard_msgs__srv__Load_Request *)(untyped_value);
  *value = *item;
}

void ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__assign_function__Load_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  ur_dashboard_msgs__srv__Load_Request * item =
    ((ur_dashboard_msgs__srv__Load_Request *)
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_function__Load_Event__request(untyped_member, index));
  const ur_dashboard_msgs__srv__Load_Request * value =
    (const ur_dashboard_msgs__srv__Load_Request *)(untyped_value);
  *item = *value;
}

bool ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__resize_function__Load_Event__request(
  void * untyped_member, size_t size)
{
  ur_dashboard_msgs__srv__Load_Request__Sequence * member =
    (ur_dashboard_msgs__srv__Load_Request__Sequence *)(untyped_member);
  ur_dashboard_msgs__srv__Load_Request__Sequence__fini(member);
  return ur_dashboard_msgs__srv__Load_Request__Sequence__init(member, size);
}

size_t ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__size_function__Load_Event__response(
  const void * untyped_member)
{
  const ur_dashboard_msgs__srv__Load_Response__Sequence * member =
    (const ur_dashboard_msgs__srv__Load_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_const_function__Load_Event__response(
  const void * untyped_member, size_t index)
{
  const ur_dashboard_msgs__srv__Load_Response__Sequence * member =
    (const ur_dashboard_msgs__srv__Load_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_function__Load_Event__response(
  void * untyped_member, size_t index)
{
  ur_dashboard_msgs__srv__Load_Response__Sequence * member =
    (ur_dashboard_msgs__srv__Load_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__fetch_function__Load_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const ur_dashboard_msgs__srv__Load_Response * item =
    ((const ur_dashboard_msgs__srv__Load_Response *)
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_const_function__Load_Event__response(untyped_member, index));
  ur_dashboard_msgs__srv__Load_Response * value =
    (ur_dashboard_msgs__srv__Load_Response *)(untyped_value);
  *value = *item;
}

void ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__assign_function__Load_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  ur_dashboard_msgs__srv__Load_Response * item =
    ((ur_dashboard_msgs__srv__Load_Response *)
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_function__Load_Event__response(untyped_member, index));
  const ur_dashboard_msgs__srv__Load_Response * value =
    (const ur_dashboard_msgs__srv__Load_Response *)(untyped_value);
  *item = *value;
}

bool ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__resize_function__Load_Event__response(
  void * untyped_member, size_t size)
{
  ur_dashboard_msgs__srv__Load_Response__Sequence * member =
    (ur_dashboard_msgs__srv__Load_Response__Sequence *)(untyped_member);
  ur_dashboard_msgs__srv__Load_Response__Sequence__fini(member);
  return ur_dashboard_msgs__srv__Load_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ur_dashboard_msgs__srv__Load_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(ur_dashboard_msgs__srv__Load_Event, request),  // bytes offset in struct
    NULL,  // default value
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__size_function__Load_Event__request,  // size() function pointer
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_const_function__Load_Event__request,  // get_const(index) function pointer
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_function__Load_Event__request,  // get(index) function pointer
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__fetch_function__Load_Event__request,  // fetch(index, &value) function pointer
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__assign_function__Load_Event__request,  // assign(index, value) function pointer
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__resize_function__Load_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(ur_dashboard_msgs__srv__Load_Event, response),  // bytes offset in struct
    NULL,  // default value
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__size_function__Load_Event__response,  // size() function pointer
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_const_function__Load_Event__response,  // get_const(index) function pointer
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__get_function__Load_Event__response,  // get(index) function pointer
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__fetch_function__Load_Event__response,  // fetch(index, &value) function pointer
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__assign_function__Load_Event__response,  // assign(index, value) function pointer
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__resize_function__Load_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_members = {
  "ur_dashboard_msgs__srv",  // message namespace
  "Load_Event",  // message name
  3,  // number of fields
  sizeof(ur_dashboard_msgs__srv__Load_Event),
  false,  // has_any_key_member_
  ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_member_array,  // message members
  ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_type_support_handle = {
  0,
  &ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_members,
  get_message_typesupport_handle_function,
  &ur_dashboard_msgs__srv__Load_Event__get_type_hash,
  &ur_dashboard_msgs__srv__Load_Event__get_type_description,
  &ur_dashboard_msgs__srv__Load_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ur_dashboard_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load_Event)() {
  ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load_Request)();
  ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load_Response)();
  if (!ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_type_support_handle.typesupport_identifier) {
    ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "ur_dashboard_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "ur_dashboard_msgs/srv/detail/load__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers ur_dashboard_msgs__srv__detail__load__rosidl_typesupport_introspection_c__Load_service_members = {
  "ur_dashboard_msgs__srv",  // service namespace
  "Load",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // ur_dashboard_msgs__srv__detail__load__rosidl_typesupport_introspection_c__Load_Request_message_type_support_handle,
  NULL,  // response message
  // ur_dashboard_msgs__srv__detail__load__rosidl_typesupport_introspection_c__Load_Response_message_type_support_handle
  NULL  // event_message
  // ur_dashboard_msgs__srv__detail__load__rosidl_typesupport_introspection_c__Load_Response_message_type_support_handle
};


static rosidl_service_type_support_t ur_dashboard_msgs__srv__detail__load__rosidl_typesupport_introspection_c__Load_service_type_support_handle = {
  0,
  &ur_dashboard_msgs__srv__detail__load__rosidl_typesupport_introspection_c__Load_service_members,
  get_service_typesupport_handle_function,
  &ur_dashboard_msgs__srv__Load_Request__rosidl_typesupport_introspection_c__Load_Request_message_type_support_handle,
  &ur_dashboard_msgs__srv__Load_Response__rosidl_typesupport_introspection_c__Load_Response_message_type_support_handle,
  &ur_dashboard_msgs__srv__Load_Event__rosidl_typesupport_introspection_c__Load_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    ur_dashboard_msgs,
    srv,
    Load
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    ur_dashboard_msgs,
    srv,
    Load
  ),
  &ur_dashboard_msgs__srv__Load__get_type_hash,
  &ur_dashboard_msgs__srv__Load__get_type_description,
  &ur_dashboard_msgs__srv__Load__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ur_dashboard_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load)(void) {
  if (!ur_dashboard_msgs__srv__detail__load__rosidl_typesupport_introspection_c__Load_service_type_support_handle.typesupport_identifier) {
    ur_dashboard_msgs__srv__detail__load__rosidl_typesupport_introspection_c__Load_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)ur_dashboard_msgs__srv__detail__load__rosidl_typesupport_introspection_c__Load_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur_dashboard_msgs, srv, Load_Event)()->data;
  }

  return &ur_dashboard_msgs__srv__detail__load__rosidl_typesupport_introspection_c__Load_service_type_support_handle;
}
