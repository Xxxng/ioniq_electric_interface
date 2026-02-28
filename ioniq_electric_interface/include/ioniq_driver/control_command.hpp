#ifndef IONIQ_ELECTRIC_INTERFACE__CONTROL_COMMAND_HPP_
#define IONIQ_ELECTRIC_INTERFACE__CONTROL_COMMAND_HPP_

#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/bool.hpp>

#include <can_msgs/msg/frame.hpp>


#include <ioniq_electric_msgs/msg/ctrl_a.hpp>
#include <ioniq_electric_msgs/msg/ctrl_b.hpp>

#include <ioniq_electric_interface/ctrl_a.hpp>
#include <ioniq_electric_interface/ctrl_b.hpp>


namespace ioniq_electric_interface
{
namespace control_command
{

struct Param
{
  std::string base_frame_id;
  double loop_rate;
  int command_timeout_ms;
};

class ControlCommand : public rclcpp::Node
{
private:
  Param param_;
  rclcpp::Subscription<ioniq_electric_msgs::msg::CtrlA>::SharedPtr ctrl_a_sub_;
  rclcpp::Subscription<ioniq_electric_msgs::msg::CtrlB>::SharedPtr ctrl_b_sub_;

  ioniq_electric_msgs::msg::CtrlA::ConstSharedPtr ctrl_a_ptr_;
  ioniq_electric_msgs::msg::CtrlB::ConstSharedPtr ctrl_b_ptr_;

  CtrlA ctrl_a_entity_;
  CtrlB ctrl_b_entity_;

  rclcpp::Time ctrl_a_received_time_;
  rclcpp::Time ctrl_b_received_time_;

  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr engage_ctrl_sub_;
  bool is_engage_;

  rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr can_frame_pub_;

  // publishing can msgs
  can_msgs::msg::Frame::ConstSharedPtr ctrl_a_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr ctrl_b_can_ptr_;

  int ctrl_a_aliv_cnt_;
  // timer
  rclcpp::TimerBase::SharedPtr timer_;

public:
  ControlCommand();
  void callbackCtrlA(const ioniq_electric_msgs::msg::CtrlA::ConstSharedPtr & msg);
  void callbackCtrlB(const ioniq_electric_msgs::msg::CtrlB::ConstSharedPtr & msg);

  void callbackEngage(const std_msgs::msg::Bool::ConstSharedPtr & msg);
  void timerCallback();

  template <typename MsgType>
  void checkAndPublishCan(
    const rclcpp::Time &received_time,
    const std::shared_ptr<const MsgType> &msg_ptr,
    const std::string &msg_name);
};

} // control_command
} // ioniq_electric_interface
#endif // IONIQ_ELECTRIC_INTERFACE__CONTROL_COMMAND_HPP_