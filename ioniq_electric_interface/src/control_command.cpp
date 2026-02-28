#include <ioniq_electric_interface/control_command.hpp>

namespace ioniq_electric_interface
{
namespace control_command
{
ControlCommand::ControlCommand() : Node("control_command")
{
  param_.base_frame_id = declare_parameter("base_frame_id", "base_link");
  param_.command_timeout_ms = declare_parameter("command_timeout_ms", 1000);
  param_.loop_rate = declare_parameter("loop_rate", 50.0);

  ctrl_a_received_time_ = this->now();
  ctrl_b_received_time_ = this->now();
  ctrl_a_aliv_cnt_ = 0;

  is_engage_ = true;

  using std::placeholders::_1;

  ctrl_a_sub_ = create_subscription<ioniq_electric_msgs::msg::CtrlA>("/ioniq/ctrl_a", 1, std::bind(&ControlCommand::callbackCtrlA, this, _1));
  ctrl_b_sub_ = create_subscription<ioniq_electric_msgs::msg::CtrlB>("/ioniq/ctrl_b", 1, std::bind(&ControlCommand::callbackCtrlB, this, _1));


  can_frame_pub_ = create_publisher<can_msgs::msg::Frame>("output/can_tx", rclcpp::QoS{1});


  timer_ = rclcpp::create_timer(
    this, get_clock(), rclcpp::Rate(param_.loop_rate).period(),
    std::bind(&ControlCommand::timerCallback, this));
}

void ControlCommand::callbackCtrlA(const ioniq_electric_msgs::msg::CtrlA::ConstSharedPtr & msg)
{
    ctrl_a_received_time_ = this->now();
    ctrl_a_ptr_ = msg;
    ctrl_a_entity_.Reset();
    ctrl_a_entity_.UpdateData(msg->eps_en, msg->eps_override_ignore, msg->eps_speed, msg->acc_en, msg->aeb_en, ctrl_a_aliv_cnt_, msg->aeb_decel_value, msg->acc_override_ignore, msg->gear_sel, msg->turn_signal);
    can_msgs::msg::Frame ctrl_a_can_msg;
    ctrl_a_can_msg.header.stamp = msg->header.stamp;
    ctrl_a_can_msg.dlc = 8;
    ctrl_a_can_msg.id = ctrl_a_entity_.ID;
    ctrl_a_can_msg.is_extended = false;
    uint8_t *signal_bits;
    signal_bits = ctrl_a_entity_.get_data();
    for (int i = 0; i < 8; i++)
    {
        ctrl_a_can_msg.data[i] = *signal_bits;
        signal_bits += 1;
    }
    if(ctrl_a_aliv_cnt_ > 255) ctrl_a_aliv_cnt_ = 0;
    else ctrl_a_aliv_cnt_++;
    ctrl_a_can_ptr_ = std::make_shared<can_msgs::msg::Frame>(ctrl_a_can_msg);
    

}

    

void ControlCommand::callbackCtrlB(const ioniq_electric_msgs::msg::CtrlB::ConstSharedPtr & msg)
{
    ctrl_b_received_time_ = this->now();
    ctrl_b_ptr_ = msg;
    ctrl_b_entity_.Reset();
    ctrl_b_entity_.UpdateData(msg->eps_cmd, msg->acc_cmd);
    can_msgs::msg::Frame ctrl_b_can_msg;
    ctrl_b_can_msg.header.stamp = msg->header.stamp;
    ctrl_b_can_msg.dlc = 8;
    ctrl_b_can_msg.id = ctrl_b_entity_.ID;
    ctrl_b_can_msg.is_extended = false;
    uint8_t *signal_bits;
    signal_bits = ctrl_b_entity_.get_data();
    for (int i = 0; i < 8; i++)
    {
        ctrl_b_can_msg.data[i] = *signal_bits;
        signal_bits += 1;
    }
    if(ctrl_a_aliv_cnt_ > 255) ctrl_a_aliv_cnt_ = 0;
    else ctrl_a_aliv_cnt_++;
    ctrl_b_can_ptr_ = std::make_shared<can_msgs::msg::Frame>(ctrl_b_can_msg);
}
    
void ControlCommand::callbackEngage(const std_msgs::msg::Bool::ConstSharedPtr & msg)
{
  is_engage_ = msg->data;
}

void ControlCommand::timerCallback()
{
    if (!is_engage_) return;

    checkAndPublishCan(ctrl_a_received_time_, ctrl_a_can_ptr_, "ctrl_a");
    checkAndPublishCan(ctrl_b_received_time_, ctrl_b_can_ptr_, "ctrl_b");
}

template <typename MsgType>
void ControlCommand::checkAndPublishCan(
    const rclcpp::Time &received_time,
    const std::shared_ptr<const MsgType> &msg_ptr,
    const std::string &msg_name)
{
    const rclcpp::Time current_time = this->now();
    const double delta_time_ms = (current_time - received_time).seconds() * 1000.0;

    if (delta_time_ms > param_.command_timeout_ms || msg_ptr == nullptr)
    {
        RCLCPP_ERROR_THROTTLE(
            get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
            "%s timeout = %f ms.", msg_name.c_str(), delta_time_ms);
        return;
    }

    can_frame_pub_->publish(*msg_ptr);
}

} // namespace control_command
} // namespace ioniq_electric_interface
