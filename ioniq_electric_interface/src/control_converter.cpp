#include <memory>
#include <string>

#include <ioniq_electric_interface/control_converter.hpp>

namespace ioniq_electric_interface
{
namespace control_converter
{
ControlConverter::ControlConverter() : Node("control_converter")
{
  // ros params
  param_.autoware_control_command_timeout =
    declare_parameter("autoware_control_command_timeout", 100);
  param_.loop_rate = declare_parameter("loop_rate", 50.0);
  param_.max_steering_angle = declare_parameter("max_steering_angle", 0.5236);
  param_.steering_factor = 450.0 / param_.max_steering_angle;

  // initialization engage
  engage_cmd_ = false;

  // initialize msgs and timestamps
  control_cmd_received_time_ = this->now();
  gear_command_received_time_ = this->now();
  acc_info_received_time_  = this->now();
  hazard_lights_cmd_received_time_ = this->now();
  turn_indicators_cmd_received_time_ = this->now();
  vehicle_cmd_emergency_received_time_ = this->now();

  // topic name 
  std::string ctrl_a_pub_topic_name = "/ioniq/ctrl_a";
  std::string ctrl_b_pub_topic_name = "/ioniq/ctrl_b";

  // publishers
  ctrl_a_pub_ =
    create_publisher<CtrlA>(ctrl_a_pub_topic_name, rclcpp::QoS(1));
  ctrl_b_pub_ =
    create_publisher<CtrlB>(ctrl_b_pub_topic_name, rclcpp::QoS(1));

  //services
  control_mode_server_ = create_service<autoware_vehicle_msgs::srv::ControlModeCommand>(
    "/control/control_mode_request",
    std::bind(
      &ControlConverter::onControlModeRequest, this, std::placeholders::_1, std::placeholders::_2));

  // subscribers
  acc_info_sub_ = create_subscription<AccInfo>(
    "/ioniq/acc_info", 1,
    std::bind(&ControlConverter::callbackAccInfo, this, std::placeholders::_1));
  
  control_cmd_sub_ = create_subscription<autoware_control_msgs::msg::Control>(
    "/control/command/control_cmd", 1,
    std::bind(&ControlConverter::callbackControlCmd, this, std::placeholders::_1));
  actuation_command_sub_ =
    create_subscription<tier4_vehicle_msgs::msg::ActuationCommandStamped>(
      "/control/command/actuation_cmd", 1,
      std::bind(&ControlConverter::callbackActuationCommand, this, std::placeholders::_1));
  gear_command_sub_ = create_subscription<autoware_vehicle_msgs::msg::GearCommand>(
    "/control/command/gear_cmd", 1,
    std::bind(&ControlConverter::callbackGearCommand, this, std::placeholders::_1));
  hazard_lights_cmd_sub_ = create_subscription<	autoware_vehicle_msgs::msg::HazardLightsCommand>(
    "/control/command/hazard_lights_cmd", 1,
    std::bind(&ControlConverter::callbackHarzardLightsCmd, this, std::placeholders::_1));
  turn_indicators_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::TurnIndicatorsCommand	>(
    "/control/command/turn_indicators_cmd", 1,
    std::bind(&ControlConverter::callbackTurnIndicatorsCmd, this, std::placeholders::_1));
  vehicle_cmd_emergency_sub_ = create_subscription<tier4_vehicle_msgs::msg::VehicleEmergencyStamped>(
    "/control/command/vehicle_cmd_emergency", 1,
    std::bind(&ControlConverter::callbackVehicleCmdEmergency, this, std::placeholders::_1));
    
  operation_mode_sub_ = create_subscription<autoware_adapi_v1_msgs::msg::OperationModeState>(
    "/api/operation_mode/state", 1,
    std::bind(&ControlConverter::callbackOperationMode, this, std::placeholders::_1));
  engage_sub_ = create_subscription<autoware_vehicle_msgs::msg::Engage>(
    "/api/autoware/get/engage", 1, 
    std::bind(&ControlConverter::callbackEngage, this, std::placeholders::_1));
  
  timer_ = rclcpp::create_timer(
    this, get_clock(), rclcpp::Rate(param_.loop_rate).period(),
    std::bind(&ControlConverter::timerCallback, this));
}

void ControlConverter::callbackEngage(
  const autoware_vehicle_msgs::msg::Engage::ConstSharedPtr & msg)
{
  // engage_received_time_ = this->now();
  engage_ptr_ = msg;
  engage_cmd_ = engage_ptr_->engage;
  // RCLCPP_INFO(get_logger(), "callbackActuationCommand: %f", actuation_command_received_time_.seconds() * 1000.0);
} 
void ControlConverter::callbackControlCmd(
  const autoware_control_msgs::msg::Control::ConstSharedPtr & msg)
{
  control_cmd_received_time_ = this->now();
  control_cmd_command_ptr_ = msg;
  // RCLCPP_INFO(get_logger(), "callbackActuationCommand: %f", actuation_command_received_time_.seconds() * 1000.0);
}

void ControlConverter::callbackActuationCommand(
  const tier4_vehicle_msgs::msg::ActuationCommandStamped::ConstSharedPtr & msg)
{
  actuation_command_received_time_ = this->now();
  actuation_command_ptr_ = msg;
  // RCLCPP_INFO(get_logger(), "callbackActuationCommand: %f", actuation_command_received_time_.seconds() * 1000.0);
}

void ControlConverter::callbackGearCommand(
  const autoware_vehicle_msgs::msg::GearCommand::ConstSharedPtr & msg)
{
  gear_command_received_time_ = this->now();
  gear_command_ptr_ = msg;
}

void ControlConverter::callbackAccInfo(const AccInfo::ConstSharedPtr & msg)
{
  acc_info_received_time_ = this->now();
  acc_info_ptr_ = msg;
}

void ControlConverter::callbackHarzardLightsCmd(const HazardLightsCommand::ConstSharedPtr & msg)
{
  hazard_lights_cmd_received_time_ = this->now();
  hazard_lights_cmd_ptr_ = msg;
}

void ControlConverter::callbackTurnIndicatorsCmd(const TurnIndicatorsCommand::ConstSharedPtr & msg)
{
  turn_indicators_cmd_received_time_ = this->now();
  turn_indicators_cmd_ptr_ = msg;
}

void ControlConverter::callbackVehicleCmdEmergency(const VehicleEmergencyStamped::ConstSharedPtr & msg)
{
  vehicle_cmd_emergency_received_time_ = this->now();
  vehicle_cmd_emergency_ptr_ = msg;
}

void ControlConverter::callbackOperationMode(const autoware_adapi_v1_msgs::msg::OperationModeState::ConstSharedPtr & msg)
{
  operation_mode_ptr_ = msg;
}

void ControlConverter::onControlModeRequest(
  const autoware_vehicle_msgs::srv::ControlModeCommand::Request::SharedPtr request,
  const autoware_vehicle_msgs::srv::ControlModeCommand::Response::SharedPtr response)
{
  if (request->mode == autoware_vehicle_msgs::srv::ControlModeCommand::Request::AUTONOMOUS) {
    engage_cmd_ = true;
    response->success = true;
    return;
  }

  if (request->mode == autoware_vehicle_msgs::srv::ControlModeCommand::Request::MANUAL) {
    engage_cmd_ = false;
    response->success = true;
    return;
  }

  RCLCPP_ERROR(get_logger(), "unsupported control_mode!!");
  engage_cmd_ = false;
  response->success = false;
  return;
}

void ControlConverter::timerCallback()
{
  const rclcpp::Time current_time = this->now();
  // const double actuation_command_delta_time_ms =
  //   (current_time - actuation_command_received_time_).seconds() * 1000.0;
  // const double gear_command_delta_time_ms =
  //   (current_time - gear_command_received_time_).seconds() * 1000.0;
  // const double acc_info_delta_time_ms =
  //   (current_time - acc_info_received_time_).seconds() * 1000.0;
  // const double hazard_lights_cmd_delta_time_ms =
  //   (current_time - hazard_lights_cmd_received_time_).seconds() * 1000.0;
  // const double turn_indicators_cmd_delta_time_ms =
  //   (current_time - turn_indicators_cmd_received_time_).seconds() * 1000.0;
  // const double vehicle_cmd_emergency_delta_time_ms =
  //   (current_time - vehicle_cmd_emergency_received_time_).seconds() * 1000.0;

  // if(actuation_command_delta_time_ms > param_.autoware_control_command_timeout
  //     || gear_command_delta_time_ms > param_.autoware_control_command_timeout
  //     || acc_info_delta_time_ms > param_.autoware_control_command_timeout
  //     || hazard_lights_cmd_delta_time_ms > param_.autoware_control_command_timeout
  //     || turn_indicators_cmd_delta_time_ms > param_.autoware_control_command_timeout
  //     || vehicle_cmd_emergency_delta_time_ms > param_.autoware_control_command_timeout
    if(  turn_indicators_cmd_ptr_==nullptr
      || hazard_lights_cmd_ptr_==nullptr
      || control_cmd_command_ptr_==nullptr
      || actuation_command_ptr_==nullptr
      || gear_command_ptr_==nullptr)
  { //debug
    // RCLCPP_ERROR_THROTTLE(
    //   get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
    //   "vital signal timeout. actuation command timeout = %f ms, gear command timeout = %f",
    //   actuation_command_delta_time_ms, gear_command_delta_time_ms);
    engage_cmd_ = false; 
  }
  // if(vehicle_cmd_emergency_ptr_!=nullptr){
  //   engage_cmd_ = !(vehicle_cmd_emergency_ptr_-> emergency);
  // }

  // sending control messages to pix dirver control command
  CtrlA ctrl_a_msg;
  CtrlB ctrl_b_msg;

  if (engage_cmd_ == true)
  {
    // ctrl_a
    ctrl_a_msg.header.stamp = current_time;
    
    // acc
    ctrl_a_msg.acc_en = 1;
    double acc = control_cmd_command_ptr_->longitudinal.acceleration;
    acc = std::max(-3.0, std::min(acc, 1.0));
    ctrl_b_msg.acc_cmd = acc;

    // steer
    ctrl_a_msg.eps_en = 1;
    ctrl_a_msg.eps_speed = 250;
    int eps_raw = actuation_command_ptr_->actuation.steer_cmd * param_.steering_factor;
    eps_raw = std::max(-450, std::min(eps_raw, 450));
    ctrl_b_msg.eps_cmd = eps_raw;

    // gear
    switch (gear_command_ptr_->command) {
      case autoware_vehicle_msgs::msg::GearCommand::DRIVE:
        ctrl_a_msg.gear_sel = static_cast<int8_t>(GEAR_DRIVE);
        break;
      case autoware_vehicle_msgs::msg::GearCommand::NEUTRAL:
        ctrl_a_msg.gear_sel = static_cast<int8_t>(GEAR_NEUTRAL);
        break;
      case autoware_vehicle_msgs::msg::GearCommand::REVERSE:
        ctrl_a_msg.gear_sel = static_cast<int8_t>(GEAR_REVERSE);
        break;
      case autoware_vehicle_msgs::msg::GearCommand::PARK:
        ctrl_a_msg.gear_sel = static_cast<int8_t>(GEAR_PARK);
        break;
      case autoware_vehicle_msgs::msg::GearCommand::NONE :
        ctrl_a_msg.gear_sel = static_cast<int8_t>(GEAR_PARK);
        break;
      default:
        ctrl_a_msg.gear_sel  = static_cast<int8_t>(GEAR_PARK);
        break;
    }
    // keep shifting and braking when target gear is different from actual gear
    // if (acc_info_ptr_->g_sel_disp != ctrl_a_msg.gear_sel ) {
    //   ctrl_b_msg.acc_cmd = -1.0;
    // }


    // turn indicators
    switch (turn_indicators_cmd_ptr_->command) {
      case autoware_vehicle_msgs::msg::TurnIndicatorsCommand::NO_COMMAND:
        ctrl_a_msg.turn_signal = static_cast<int8_t>(TURN_NONE);
        break;
      case autoware_vehicle_msgs::msg::TurnIndicatorsCommand::DISABLE:
        ctrl_a_msg.turn_signal = static_cast<int8_t>(TURN_NONE);
        break;
      case autoware_vehicle_msgs::msg::TurnIndicatorsCommand::ENABLE_LEFT:
        ctrl_a_msg.turn_signal = static_cast<int8_t>(TURN_LEFT);
        break;
      case autoware_vehicle_msgs::msg::TurnIndicatorsCommand::ENABLE_RIGHT:
        ctrl_a_msg.turn_signal = static_cast<int8_t>(TURN_RIGHT);
        break;
      default:
        ctrl_a_msg.turn_signal  = static_cast<int8_t>(TURN_NONE);
        break;
    }

    // hazard
    if (hazard_lights_cmd_ptr_->command == HazardLightsCommand::ENABLE)
      ctrl_a_msg.turn_signal = static_cast<int8_t>(TURN_HAZARD);

    // parking
    // park_ctrl_msg.park_en_ctrl = true;
    // if(operation_mode_ptr_->mode == operation_mode_ptr_->STOP){
    //   park_ctrl_msg.park_target = true;
    // } else{
    //   park_ctrl_msg.park_target = false;
    // }
    // parking_brake = 0;
    // RCLCPP_INFO(get_logger(), "remote_control mode 0");
  }
  else if (engage_cmd_ == false)
  {
    // ctrl_a
    ctrl_a_msg.header.stamp = current_time;

    // acc
    ctrl_a_msg.acc_en = 1;
    ctrl_b_msg.acc_cmd = -2.0;

    // steer
    ctrl_a_msg.eps_en = 1;
    ctrl_a_msg.eps_speed = 0;
    ctrl_b_msg.eps_cmd = 0.0;

    // gear
    ctrl_a_msg.gear_sel  = static_cast<int8_t>(GEAR_PARK);

    // // keep shifting and braking when target gear is different from actual gear
    // if (acc_info_ptr_->g_sel_disp != ctrl_a_msg.gear_sel ) {
    //   ctrl_b_msg.acc_cmd = -1.0;
    // }

    // hazard
    ctrl_a_msg.turn_signal = 1;
   

    // // parking
    // park_ctrl_msg.header.stamp = current_time;
    // park_ctrl_msg.park_en_ctrl = true;
    // if(current_velocity == 0){
    //   park_ctrl_msg.park_target = true;
    //   // brake
    //   parking_brake = 0;
    //   brake_ctrl_msg.header.stamp = current_time;
    //   brake_ctrl_msg.brake_pedal_target = parking_brake;
    //   brake_ctrl_msg.brake_en_ctrl = 1;
    // } else{
    //   park_ctrl_msg.park_target = false;
    //   // brake
    //   brake_ctrl_msg.header.stamp = current_time;
    //   brake_ctrl_msg.brake_pedal_target = parking_brake;
    //   brake_ctrl_msg.brake_en_ctrl = 1;
    // }
    // RCLCPP_INFO(get_logger(), "remote_control mode 1");
  }

  // publishing msgs
  ctrl_a_pub_->publish(ctrl_a_msg);
  ctrl_b_pub_->publish(ctrl_b_msg);
}
} // namespace control_converter
} // namespace ioniq_electric_interface