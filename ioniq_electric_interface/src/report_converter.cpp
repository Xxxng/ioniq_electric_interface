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

#include <ioniq_electric_interface/report_converter.hpp>

namespace ioniq_electric_interface
{
namespace report_converter
{
ReportConverter::ReportConverter() : rclcpp::Node("report_converter")
{
  // initialize node parameters
  param_.report_msg_timeout_ms =
    declare_parameter("report_msg_timeout_ms", 1000);
  param_.loop_rate = declare_parameter("loop_rate", 60.0);
  param_.max_steering_angle = declare_parameter("max_steering_angle", 0.5236);
  param_.steering_factor = param_.max_steering_angle / 450.0;
  param_.base_frame_id = declare_parameter("base_frame_id", "base_link");

  // initialize msg received timestamps
  eps_info_received_timestamp_ = this->now();
  acc_info_received_timestamp_ = this->now();
  spd_info_received_timestamp_ = this->now();
  imu_info_received_timestamp_ = this->now();
  rad_info_received_timestamp_ = this->now();
  // additional_sig_received_timestamp_ = this->now();
  

  // topic name 
  std::string eps_info_sub_topic_name = "/ioniq/eps_info";
  std::string acc_info_sub_topic_name = "/ioniq/acc_info";
  std::string spd_info_sub_topic_name = "/ioniq/spd_info";
  std::string imu_info_sub_topic_name = "/ioniq/imu_info";
  std::string rad_info_sub_topic_name = "/ioniq/rad_info";
  // std::string additional_sig_sub_topic_name = "/ioniq/additional_sig";

  // initialize subscribers
  eps_info_sub_ = create_subscription<ioniq_electric_msgs::msg::EpsInfo>(
    eps_info_sub_topic_name, 1,
    std::bind(&ReportConverter::epsInfoCallback, this, std::placeholders::_1));
  acc_info_sub_ = create_subscription<ioniq_electric_msgs::msg::AccInfo>(
    acc_info_sub_topic_name, 1,
    std::bind(&ReportConverter::accInfoCallback, this, std::placeholders::_1));
  spd_info_sub_ = create_subscription<ioniq_electric_msgs::msg::SpdInfo>(
    spd_info_sub_topic_name, 1,
    std::bind(&ReportConverter::spdInfoCallback, this, std::placeholders::_1));
    
  imu_info_sub_ = create_subscription<ioniq_electric_msgs::msg::ImuInfo>(
    imu_info_sub_topic_name, 1,
    std::bind(&ReportConverter::imuInfoCallback, this, std::placeholders::_1));

  rad_info_sub_ = create_subscription<ioniq_electric_msgs::msg::RadInfo>(
    rad_info_sub_topic_name, 1,
    std::bind(&ReportConverter::radInfoCallback, this, std::placeholders::_1));

  // additional_sig_sub_ = create_subscription<ioniq_electric_msgs::msg::AdditionalSig>(
  //   additional_sig_sub_topic_name, 1,
  //   std::bind(&ReportConverter::additionalSigCallback, this, std::placeholders::_1));

  // initialize publishers
  control_mode_pub_ = create_publisher<autoware_vehicle_msgs::msg::ControlModeReport>(
    "/vehicle/status/control_mode", rclcpp::QoS{1});
  vehicle_twist_pub_ = create_publisher<autoware_vehicle_msgs::msg::VelocityReport>(
    "/vehicle/status/velocity_status", rclcpp::QoS{1});
  steering_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::SteeringReport>(
    "/vehicle/status/steering_status", rclcpp::QoS{1});
  gear_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::GearReport>(
    "/vehicle/status/gear_status", rclcpp::QoS{1});
  turn_indicators_status_pub_ =
    create_publisher<autoware_vehicle_msgs::msg::TurnIndicatorsReport>(
      "/vehicle/status/turn_indicators_status", rclcpp::QoS{1});
  hazard_lights_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::HazardLightsReport>(
    "/vehicle/status/hazard_lights_status", rclcpp::QoS{1});
  actuation_status_pub_ = create_publisher<tier4_vehicle_msgs::msg::ActuationStatusStamped>(
    "/vehicle/status/actuation_status", 1);
  // steering_wheel_status_pub_ =
  //   create_publisher<tier4_vehicle_msgs::msg::SteeringWheelStatusStamped>(
  //     "/vehicle/status/steering_wheel_status", 1);
  // door_status_pub_ =
  //   create_publisher<tier4_api_msgs::msg::DoorStatus>("/vehicle/status/door_status", 1);
  
  // initialize of timer
  timer_ = rclcpp::create_timer(
    this, get_clock(), rclcpp::Rate(param_.loop_rate).period(),
    std::bind(&ReportConverter::timerCallback, this));
}

// timer callback function
void ReportConverter::timerCallback()
{
  const rclcpp::Time current_time = this->now();
  // const double spd_info_delta_time_ms =
  //   (current_time - spd_info_received_timestamp_).seconds() * 1000.0;
  // const double acc_info_delta_time_ms =
  //   (current_time - acc_info_received_timestamp_).seconds() * 1000.0;
  // const double eps_info_delta_time_ms =
  //   (current_time - eps_info_received_timestamp_).seconds() * 1000.0;
  // const double rad_info_delta_time_ms =
  //   (current_time - rad_info_received_timestamp_).seconds() * 1000.0;
  // const double imu_info_delta_time_ms = 
  //   (current_time - imu_info_received_timestamp_).seconds() * 1000.0;
  // const double additional_sig_delta_time_ms =
  //   (current_time - additional_sig_received_timestamp_).seconds() * 1000.0;

  if (eps_info_ptr_ == nullptr || acc_info_ptr_ == nullptr
      // spd_info_delta_time_ms>param_.report_msg_timeout_ms || acc_info_delta_time_ms>param_.report_msg_timeout_ms || 
      // eps_info_delta_time_ms>param_.report_msg_timeout_ms || rad_info_delta_time_ms>param_.report_msg_timeout_ms ||
      // imu_info_delta_time_ms>param_.report_msg_timeout_ms
      )
  {
    // RCLCPP_ERROR_THROTTLE(
    //   get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(), "vital msgs not received or timeout");
    return;
  }

  // 1. making gear msg
  gear_msg_.stamp = current_time;
  switch (acc_info_ptr_->g_sel_disp) {
    case static_cast<int8_t>(GEAR_DRIVE):
      gear_msg_.report = autoware_vehicle_msgs::msg::GearReport::DRIVE;
      break;
    case static_cast<int8_t>(GEAR_NEUTRAL):
      gear_msg_.report = autoware_vehicle_msgs::msg::GearReport::NEUTRAL;
      break;
    case static_cast<int8_t>(GEAR_REVERSE):
      gear_msg_.report = autoware_vehicle_msgs::msg::GearReport::REVERSE;
      break;
    case static_cast<int8_t>(GEAR_PARK):
      gear_msg_.report = autoware_vehicle_msgs::msg::GearReport::PARK;
      break;
    default:
      gear_msg_.report = autoware_vehicle_msgs::msg::GearReport::NONE;
      break;
  }
  gear_status_pub_->publish(gear_msg_);

  // 2. making velocity
  velocity_report_msg_.header.frame_id = param_.base_frame_id;
  velocity_report_msg_.header.stamp = current_time;
  velocity_report_msg_.longitudinal_velocity = acc_info_ptr_->vs / 3.6;
  vehicle_twist_pub_->publish(velocity_report_msg_);

  // 3. make steering angle
  steer_report_msg_.stamp = current_time;
  steer_report_msg_.steering_tire_angle = eps_info_ptr_->str_ang * param_.steering_factor;
  steering_status_pub_->publish(steer_report_msg_);

  // 4. make control mode
  control_mode_report_msg_.stamp = current_time;
  control_mode_report_msg_.mode = 1;
  // switch (->vehicle_mode_state)
  // {
  // case static_cast<int8_t>(VEHICLE_Manual_Remote_Mode):
  //   control_mode_report_msg_.mode = autoware_vehicle_msgs::msg::ControlModeReport::MANUAL;
  //   break;
  // case static_cast<int8_t>(VEHICLE_Auto_Mode):
  //   control_mode_report_msg_.mode = autoware_vehicle_msgs::msg::ControlModeReport::AUTONOMOUS;
  //   break;
  // case static_cast<int8_t>(VEHICLE_Standby_Mode):
  //   control_mode_report_msg_.mode = autoware_vehicle_msgs::msg::ControlModeReport::AUTONOMOUS;
  //   break;
  // case static_cast<int8_t>(VEHICLE_Emergency_Mode):
  //   control_mode_report_msg_.mode = autoware_vehicle_msgs::msg::ControlModeReport::DISENGAGED;
  //   break;
  // default:
  //   control_mode_report_msg_.mode = autoware_vehicle_msgs::msg::ControlModeReport::NOT_READY;
  //   break;
  // }
  control_mode_pub_->publish(control_mode_report_msg_);

  // 5. hazard lights status
  hazard_lights_report_msg_.stamp = current_time;
  if(acc_info_ptr_->hazard_en == 1)
  {
    hazard_lights_report_msg_.report = autoware_vehicle_msgs::msg::HazardLightsReport::ENABLE;
  }else{
    hazard_lights_report_msg_.report = autoware_vehicle_msgs::msg::HazardLightsReport::DISABLE;
  }

  // 6. turn indicators
  turn_indicators_report_msg_.stamp = current_time;
  if (acc_info_ptr_->turn_left_en == 1) {
    turn_indicators_report_msg_.report =
      autoware_vehicle_msgs::msg::TurnIndicatorsReport::ENABLE_LEFT;
  } else if(acc_info_ptr_->turn_right_en==1) {
    turn_indicators_report_msg_.report =
      autoware_vehicle_msgs::msg::TurnIndicatorsReport::ENABLE_RIGHT;
  } else {
    turn_indicators_report_msg_.report =
      autoware_vehicle_msgs::msg::TurnIndicatorsReport::DISABLE;
  }
  turn_indicators_status_pub_->publish(turn_indicators_report_msg_);

  // 7. acutation status
  actuation_status_stamped_msg_.header.stamp = current_time;
  actuation_status_stamped_msg_.header.frame_id = "base_link";
  double acc = acc_info_ptr_->long_accel;
  if (acc >=0.0) {
    actuation_status_stamped_msg_.status.accel_status = acc;
    actuation_status_stamped_msg_.status.brake_status = 0.0;
  } else {
    actuation_status_stamped_msg_.status.accel_status = 0.0;
    actuation_status_stamped_msg_.status.brake_status = -acc;
  }
  actuation_status_stamped_msg_.status.steer_status = eps_info_ptr_->str_ang * param_.steering_factor;
  actuation_status_pub_->publish(actuation_status_stamped_msg_);

  //additional_sig_ptr_->accelerator_pedal_position / 100.0
  // to be done, tier4 msgs
}

// sub callback function
void ReportConverter::epsInfoCallback(const ioniq_electric_msgs::msg::EpsInfo::ConstSharedPtr &msg)
{
  eps_info_received_timestamp_ = this->now();
  eps_info_ptr_ = msg;
}

void ReportConverter::accInfoCallback(const ioniq_electric_msgs::msg::AccInfo::ConstSharedPtr &msg)
{
  acc_info_received_timestamp_ = this->now();
  acc_info_ptr_= msg;
}

void ReportConverter::spdInfoCallback(const ioniq_electric_msgs::msg::SpdInfo::ConstSharedPtr &msg)
{
  spd_info_received_timestamp_ = this->now();
  spd_info_ptr_ = msg;
}

void ReportConverter::imuInfoCallback(const ioniq_electric_msgs::msg::ImuInfo::ConstSharedPtr &msg)
{
  imu_info_received_timestamp_ = this->now();
  imu_info_ptr_ = msg;
}

void ReportConverter::radInfoCallback(const ioniq_electric_msgs::msg::RadInfo::ConstSharedPtr &msg)
{
  rad_info_received_timestamp_ = this->now();
  rad_info_ptr_ = msg;
}

// void ReportConverter::additionalSigCallback(const ioniq_electric_msgs::msg::AdditionalSig::ConstSharedPtr &msg)
// {
//   additional_sig_received_timestamp_ = this->now();
//   additional_sig_ptr_ = msg;
// }

} // namespace report_converter
} // namespace ioniq_electric_interface