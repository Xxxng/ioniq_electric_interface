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

#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>

// autoware_msgs
#include <autoware_vehicle_msgs/msg/control_mode_report.hpp>
#include <autoware_vehicle_msgs/msg/gear_report.hpp>
#include <autoware_vehicle_msgs/msg/hazard_lights_report.hpp>
#include <autoware_vehicle_msgs/msg/steering_report.hpp>
#include <autoware_vehicle_msgs/msg/turn_indicators_report.hpp>
#include <autoware_vehicle_msgs/msg/velocity_report.hpp>

// tier4_msgs
#include <tier4_vehicle_msgs/msg/actuation_status_stamped.hpp>
#include <tier4_vehicle_msgs/msg/steering_wheel_status_stamped.hpp>
// #include <tier4_api_msgs/msg/door_status.hpp>

// ioniq_electric_msgs
#include <ioniq_electric_msgs/msg/acc_info.hpp>
#include <ioniq_electric_msgs/msg/eps_info.hpp>
#include <ioniq_electric_msgs/msg/spd_info.hpp>
#include <ioniq_electric_msgs/msg/eait_info_imu.hpp>
#include <ioniq_electric_msgs/msg/rad_info.hpp>
#include <ioniq_electric_msgs/msg/additional_sig.hpp>


namespace ioniq_electric_interface
{
namespace report_converter
{
enum {
  GEAR_PARK    = 0,  // P
  GEAR_REVERSE = 7,  // R
  GEAR_NEUTRAL = 6,  // N
  GEAR_DRIVE   = 5   // D
};
enum { Disable, Enable };
enum {
  VEHICLE_Manual_Remote_Mode,
  VEHICLE_Auto_Mode,
  VEHICLE_Emergency_Mode,
  VEHICLE_Standby_Mode
};

enum { DOOR_OPENING, DOOR_NONE };


/**
 * @brief param structure of report converter node
 * @param period loop rate of publishers in hz
 * @param max_steering_angle max steering angle in radians
 * @param report_msg_timeout_ms timeout threshold of report msg from ioniq interface in ms
 * @param base_frame_id frame id of vehicle
 * @param steering_factor the factor that convert steering feedback signal value to autoware steering value
 */
struct Param
{
  double loop_rate;           // hz
  double max_steering_angle;  // radians
  int report_msg_timeout_ms;  // ms
  std::string base_frame_id;  // vehicle frame id
  double steering_factor;
};

class ReportConverter : public rclcpp::Node
{
private:
  Param param_;
  double steering_factor_;

  // publishers to Autoware
  rclcpp::Publisher<autoware_vehicle_msgs::msg::ControlModeReport>::SharedPtr control_mode_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::VelocityReport>::SharedPtr vehicle_twist_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::SteeringReport>::SharedPtr steering_status_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::GearReport>::SharedPtr gear_status_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::TurnIndicatorsReport>::SharedPtr turn_indicators_status_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::HazardLightsReport>::SharedPtr hazard_lights_status_pub_;
  
  rclcpp::Publisher<tier4_vehicle_msgs::msg::ActuationStatusStamped>::SharedPtr actuation_status_pub_;
  rclcpp::Publisher<tier4_vehicle_msgs::msg::SteeringWheelStatusStamped>::SharedPtr steering_wheel_status_pub_;
  // rclcpp::Publisher<tier4_api_msgs::msg::DoorStatus>::SharedPtr door_status_pub_;
  
  // subscribers from ioniq interface
  rclcpp::Subscription<ioniq_electric_msgs::msg::EpsInfo>::SharedPtr eps_info_sub_;
  rclcpp::Subscription<ioniq_electric_msgs::msg::AccInfo>::SharedPtr acc_info_sub_;
  rclcpp::Subscription<ioniq_electric_msgs::msg::SpdInfo>::SharedPtr spd_info_sub_;
  rclcpp::Subscription<ioniq_electric_msgs::msg::EaitInfoImu>::SharedPtr eait_info_imu_sub_;
  rclcpp::Subscription<ioniq_electric_msgs::msg::RadInfo>::SharedPtr rad_info_sub_;
  rclcpp::Subscription<ioniq_electric_msgs::msg::AdditionalSig>::SharedPtr additional_sig_sub_;

  // timers
  rclcpp::TimerBase::ConstSharedPtr timer_;

  // msg shared ptrs
  ioniq_electric_msgs::msg::EpsInfo::ConstSharedPtr eps_info_ptr_;
  ioniq_electric_msgs::msg::AccInfo::ConstSharedPtr acc_info_ptr_;
  ioniq_electric_msgs::msg::SpdInfo::ConstSharedPtr spd_info_ptr_;
  ioniq_electric_msgs::msg::EaitInfoImu::ConstSharedPtr eait_info_imu_ptr_;
  ioniq_electric_msgs::msg::RadInfo::ConstSharedPtr rad_info_ptr_;
  ioniq_electric_msgs::msg::AdditionalSig::ConstSharedPtr additional_sig_ptr_;

  // msg received timestamps
  rclcpp::Time eps_info_received_timestamp_;
  rclcpp::Time acc_info_received_timestamp_;
  rclcpp::Time spd_info_received_timestamp_;
  rclcpp::Time eait_info_imu_received_timestamp_;
  rclcpp::Time rad_info_received_timestamp_;
  rclcpp::Time additional_sig_received_timestamp_;

  // autoware msgs
  autoware_vehicle_msgs::msg::GearReport gear_msg_;
  autoware_vehicle_msgs::msg::ControlModeReport control_mode_report_msg_;
  autoware_vehicle_msgs::msg::HazardLightsReport hazard_lights_report_msg_;       
  autoware_vehicle_msgs::msg::SteeringReport steer_report_msg_;                   
  autoware_vehicle_msgs::msg::VelocityReport velocity_report_msg_;                
  autoware_vehicle_msgs::msg::TurnIndicatorsReport turn_indicators_report_msg_;   
  // tier4 msgs
  tier4_vehicle_msgs::msg::ActuationStatusStamped actuation_status_stamped_msg_;
  // tier4_vehicle_msgs::msg::SteeringWheelStatusStamped steering_wheel_status_msg_;
  // tier4_api_msgs::msg::DoorStatus door_status_msg;

public:
  ReportConverter();
  void timerCallback();
  void epsInfoCallback(const ioniq_electric_msgs::msg::EpsInfo::ConstSharedPtr &msg);
  void accInfoCallback(const ioniq_electric_msgs::msg::AccInfo::ConstSharedPtr &msg);
  void spdInfoCallback(const ioniq_electric_msgs::msg::SpdInfo::ConstSharedPtr &msg);
  void eaitInfoImuCallback(const ioniq_electric_msgs::msg::EaitInfoImu::ConstSharedPtr &msg);
  void radInfoCallback(const ioniq_electric_msgs::msg::RadInfo::ConstSharedPtr &msg);
  void additionalSigCallback(const ioniq_electric_msgs::msg::AdditionalSig::ConstSharedPtr &msg);
};
} // report_converter
} // ioniq_electric_interface