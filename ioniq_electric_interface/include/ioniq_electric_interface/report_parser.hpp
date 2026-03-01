#ifndef IONIQ_ELECTRIC_INTERFACE__REPORT_PARSER_HPP_
#define IONIQ_ELECTRIC_INTERFACE__REPORT_PARSER_HPP_

#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/header.hpp>

#include <can_msgs/msg/frame.hpp>

#include <ioniq_electric_msgs/msg/eps_info.hpp>
#include <ioniq_electric_msgs/msg/acc_info.hpp>
#include <ioniq_electric_msgs/msg/spd_info.hpp>
#include <ioniq_electric_msgs/msg/imu_info.hpp>
#include <ioniq_electric_msgs/msg/rad_info.hpp>
#include <ioniq_electric_msgs/msg/additional_sig.hpp>

#include <ioniq_electric_interface/eps_info.hpp>
#include <ioniq_electric_interface/acc_info.hpp>
#include <ioniq_electric_interface/spd_info.hpp>
#include <ioniq_electric_interface/imu_info.hpp>
#include <ioniq_electric_interface/rad_info.hpp>
#include <ioniq_electric_interface/additional_sig.hpp>


namespace ioniq_electric_interface
{
namespace report_parser
{

/**
 * @brief param structure of report parser node
 * @param base_frame_id frame id of vehicle
 * @param loop_rate loop rate of publishers in hz
 * @param report_timeout_ms timeout threshold of report can Frame msg from canbus driver
 */
struct Param
{
  std::string base_frame_id;
  double loop_rate;
  int report_timeout_ms;
};

class ReportParser : public rclcpp::Node
{
private:
  // parameters of node
  Param param_;

  // is publish subscrber
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr is_publish_sub_;
  bool is_publish_;

  // subscribers from socketcan interface
  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr can_frame_sub_;

  // publishers
  rclcpp::Publisher<ioniq_electric_msgs::msg::EpsInfo>::SharedPtr eps_info_pub_;
  rclcpp::Publisher<ioniq_electric_msgs::msg::AccInfo>::SharedPtr acc_info_pub_;
  rclcpp::Publisher<ioniq_electric_msgs::msg::SpdInfo>::SharedPtr spd_info_pub_;
  rclcpp::Publisher<ioniq_electric_msgs::msg::ImuInfo>::SharedPtr imu_info_pub_;
  rclcpp::Publisher<ioniq_electric_msgs::msg::RadInfo>::SharedPtr rad_info_pub_;
  rclcpp::Publisher<ioniq_electric_msgs::msg::AdditionalSig>::SharedPtr additional_sig_pub_;


  // publish msgs
  ioniq_electric_msgs::msg::EpsInfo::ConstSharedPtr eps_info_ptr_;
  ioniq_electric_msgs::msg::AccInfo::ConstSharedPtr acc_info_ptr_;
  ioniq_electric_msgs::msg::SpdInfo::ConstSharedPtr spd_info_ptr_;
  ioniq_electric_msgs::msg::ImuInfo::ConstSharedPtr imu_info_ptr_;
  ioniq_electric_msgs::msg::RadInfo::ConstSharedPtr rad_info_ptr_;
  ioniq_electric_msgs::msg::AdditionalSig::ConstSharedPtr additional_sig_ptr_;


  // can frame entities
  EpsInfo eps_info_entity_;
  AccInfo acc_info_entity_;
  SpdInfo spd_info_entity_;
  ImuInfo imu_info_entity_;
  RadInfo rad_info_entity_;
  AdditionalSig additional_sig_entity_;


  // msg reveived time
  rclcpp::Time eps_info_received_time_;
  rclcpp::Time acc_info_received_time_;
  rclcpp::Time spd_info_received_time_;
  rclcpp::Time imu_info_received_time_;
  rclcpp::Time rad_info_received_time_;
  rclcpp::Time additional_sig_received_time_;


  // timer
  rclcpp::TimerBase::SharedPtr timer_;

public:
  ReportParser();
  void callbackCan(const can_msgs::msg::Frame::ConstSharedPtr & msg);
  void callbackIsPublish(const std_msgs::msg::Bool::ConstSharedPtr & msg);
  void timerCallback();

  template <typename MsgType>
  void checkAndPublishMessage(
    const rclcpp::Time &received_time, 
    const std::shared_ptr<const MsgType> &msg_ptr, 
    const std::shared_ptr<rclcpp::Publisher<MsgType>> &pub,
    const std::string &msg_name);
  };
} // report_parser
} // ioniq_electric_interface
#endif // IONIQ_ELECTRIC_INTERFACE__REPORT_PARSER_HPP_