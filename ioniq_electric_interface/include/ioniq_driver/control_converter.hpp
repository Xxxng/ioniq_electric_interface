// Copyright 2023 Pixmoving, Inc. 
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef IONIQ_ELECTRIC_INTERFACE__CONTROL_CONVERTER_HPP_
#define IONIQ_ELECTRIC_INTERFACE__CONTROL_CONVERTER_HPP_

#include <memory>
#include <string>
//ros
#include <rclcpp/rclcpp.hpp>

// autoware
#include <autoware_vehicle_msgs/msg/gear_command.hpp>
#include <autoware_vehicle_msgs/srv/control_mode_command.hpp>
#include "autoware_vehicle_msgs/msg/hazard_lights_command.hpp"
#include "autoware_vehicle_msgs/msg/turn_indicators_command.hpp"
#include <autoware_control_msgs/msg/control.hpp>
#include <autoware_adapi_v1_msgs/msg/operation_mode_state.hpp>
#include "tier4_vehicle_msgs/msg/vehicle_emergency_stamped.hpp"
#include "tier4_vehicle_msgs/msg/actuation_command_stamped.hpp"
#include <autoware_vehicle_msgs/msg/engage.hpp>

// ioniq control
#include <ioniq_electric_msgs/msg/ctrl_a.hpp>
#include <ioniq_electric_msgs/msg/ctrl_b.hpp>

// ioniq report
#include <ioniq_electric_msgs/msg/acc_info.hpp>


namespace ioniq_electric_interface
{
namespace control_converter
{

using CtrlA = ioniq_electric_msgs::msg::CtrlA;
using CtrlB = ioniq_electric_msgs::msg::CtrlB;
using AccInfo = ioniq_electric_msgs::msg::AccInfo;
using HazardLightsCommand = autoware_vehicle_msgs::msg::HazardLightsCommand;
using TurnIndicatorsCommand = autoware_vehicle_msgs::msg::TurnIndicatorsCommand;
using VehicleEmergencyStamped = tier4_vehicle_msgs::msg::VehicleEmergencyStamped;
using Control = autoware_control_msgs::msg::Control;
using ActuationCommandStamped = tier4_vehicle_msgs::msg::ActuationCommandStamped;
using GearCommand = autoware_vehicle_msgs::msg::GearCommand;
using OperationModeState = autoware_adapi_v1_msgs::msg::OperationModeState;
using Engage = autoware_vehicle_msgs::msg::Engage;

// chassis gear control and report
enum {
  GEAR_PARK    = 0,  // P
  GEAR_REVERSE = 7,  // R
  GEAR_NEUTRAL = 6,  // N
  GEAR_DRIVE   = 5   // D
};

enum {
  TURN_NONE = 0,
  TURN_RIGHT = 1,
  TURN_HAZARD = 2,
  TURN_LEFT = 4
};
/**
 * @brief node parameter
 * @param loop_rate loop rate of publisher
 * @param max_steerig_angle max steering angle in radians
 * @param steering_factor the rate to convert steering angle to steering command signal value
 * @param autoware_control_command_timeout control command timeout threshold in ms
 */
struct Param
{
  double loop_rate;                     // hz
  double max_steering_angle;            // radians
  double steering_factor;               //
  int autoware_control_command_timeout; // ms
};

class ControlConverter : public rclcpp::Node
{
private:
  // parameters
  Param param_;
  bool engage_cmd_;

  // shared msgs
  Control::ConstSharedPtr control_cmd_command_ptr_;
  ActuationCommandStamped::ConstSharedPtr actuation_command_ptr_;
  GearCommand::ConstSharedPtr gear_command_ptr_;
  AccInfo::ConstSharedPtr acc_info_ptr_;
  HazardLightsCommand::ConstSharedPtr hazard_lights_cmd_ptr_;
  TurnIndicatorsCommand::ConstSharedPtr turn_indicators_cmd_ptr_;
  VehicleEmergencyStamped::ConstSharedPtr vehicle_cmd_emergency_ptr_;
  OperationModeState::ConstSharedPtr operation_mode_ptr_;
  Engage::ConstSharedPtr engage_ptr_;

  // timestamps
  rclcpp::Time acc_info_received_time_;
  rclcpp::Time gear_command_received_time_;
  rclcpp::Time actuation_command_received_time_;
  rclcpp::Time control_cmd_received_time_;
  rclcpp::Time hazard_lights_cmd_received_time_;
  rclcpp::Time turn_indicators_cmd_received_time_;
  rclcpp::Time vehicle_cmd_emergency_received_time_;

  // subscribers
  rclcpp::Subscription<Engage>::ConstSharedPtr
    engage_sub_;
  rclcpp::Subscription<ActuationCommandStamped>::ConstSharedPtr
    actuation_command_sub_;
  rclcpp::Subscription<GearCommand>::ConstSharedPtr
    gear_command_sub_;
  rclcpp::Subscription<AccInfo>::ConstSharedPtr
    acc_info_sub_;
  rclcpp::Subscription<HazardLightsCommand>::ConstSharedPtr
    hazard_lights_cmd_sub_;
  rclcpp::Subscription<TurnIndicatorsCommand>::ConstSharedPtr
    turn_indicators_cmd_sub_;
  rclcpp::Subscription<VehicleEmergencyStamped>::ConstSharedPtr
    vehicle_cmd_emergency_sub_;
  rclcpp::Subscription<Control>::ConstSharedPtr
    control_cmd_sub_;
  rclcpp::Subscription<OperationModeState>::ConstSharedPtr
    operation_mode_sub_;

  // services
  rclcpp::Service<autoware_vehicle_msgs::srv::ControlModeCommand>::SharedPtr control_mode_server_;

  // publishers
  rclcpp::Publisher<CtrlA>::SharedPtr ctrl_a_pub_;
  rclcpp::Publisher<CtrlB>::SharedPtr ctrl_b_pub_;

  // timer
  rclcpp::TimerBase::SharedPtr timer_;

public:
  ControlConverter();
  void callbackEngage(const Engage::ConstSharedPtr & msg);
  void callbackAccInfo(const AccInfo::ConstSharedPtr & msg);
  void callbackControlCmd(const Control::ConstSharedPtr & msg);
  void callbackActuationCommand(const ActuationCommandStamped::ConstSharedPtr & msg);
  void callbackGearCommand(const GearCommand::ConstSharedPtr & msg);
  void callbackHarzardLightsCmd(const HazardLightsCommand::ConstSharedPtr & msg);
  void callbackTurnIndicatorsCmd(const TurnIndicatorsCommand::ConstSharedPtr & msg);
  void callbackVehicleCmdEmergency(const VehicleEmergencyStamped::ConstSharedPtr & msg);
  void callbackOperationMode(const OperationModeState::ConstSharedPtr & msg);
  void onControlModeRequest(
    const autoware_vehicle_msgs::srv::ControlModeCommand::Request::SharedPtr request,
    const autoware_vehicle_msgs::srv::ControlModeCommand::Response::SharedPtr response);

  void timerCallback();
};

} // namespace control_converter
} // namespace ioniq_electric_interface

#endif // IONIQ_ELECTRIC_INTERFACE__CONTROL_CONVERTER_HPP_