#include <ioniq_electric_interface/report_parser.hpp>

namespace ioniq_electric_interface
{
namespace report_parser
{
ReportParser::ReportParser() : Node("report_parser")
{
  // ros params
  param_.base_frame_id = declare_parameter("base_frame_id", "base_link");
  param_.report_timeout_ms = declare_parameter("report_timeout_ms", 1000);
  param_.loop_rate = declare_parameter("loop_rate", 50.0);

  // // initialize msg received time
  /** example
  brake_command_received_time_ = this->now();
  **/
  eps_info_received_time_ = this->now();
  acc_info_received_time_ = this->now();
  spd_info_received_time_ = this->now();
  imu_info_received_time_ = this->now();
  rad_info_received_time_ = this->now();
  additional_sig_received_time_ = this->now();

  is_publish_ = true;

  using std::placeholders::_1;

  /* subscriber */
  {
    can_frame_sub_ = create_subscription<can_msgs::msg::Frame>(
      "input/can_rx", 1, std::bind(&ReportParser::callbackCan, this, _1));
    is_publish_sub_ = create_subscription<std_msgs::msg::Bool>(
      "input/is_publish", 1, std::bind(&ReportParser::callbackIsPublish, this, _1));
  }

  /* publisher */
  {
    eps_info_pub_ = create_publisher<ioniq_electric_msgs::msg::EpsInfo>("/ioniq/eps_info", rclcpp::QoS{1});
    acc_info_pub_ = create_publisher<ioniq_electric_msgs::msg::AccInfo>("/ioniq/acc_info", rclcpp::QoS{1});
    spd_info_pub_ = create_publisher<ioniq_electric_msgs::msg::SpdInfo>("/ioniq/spd_info", rclcpp::QoS{1});
    imu_info_pub_ = create_publisher<ioniq_electric_msgs::msg::ImuInfo>("/ioniq/imu_info", rclcpp::QoS{1});
    rad_info_pub_ = create_publisher<ioniq_electric_msgs::msg::RadInfo>("/ioniq/rad_info", rclcpp::QoS{1});
    additional_sig_pub_ = create_publisher<ioniq_electric_msgs::msg::AdditionalSig>("/ioniq/additional_sig", rclcpp::QoS{1});
  }
  {
    // timer
    timer_ = rclcpp::create_timer(
      this, get_clock(), rclcpp::Rate(param_.loop_rate).period(),
      std::bind(&ReportParser::timerCallback, this));
  }
}

// calback is publish
void ReportParser::callbackIsPublish(const std_msgs::msg::Bool::ConstSharedPtr & msg)
{
  is_publish_ = msg->data;
}

// callback can
void ReportParser::callbackCan(const can_msgs::msg::Frame::ConstSharedPtr & msg)
{
  std_msgs::msg::Header header;
  header.frame_id = param_.base_frame_id;
  header.stamp = msg->header.stamp;

  ioniq_electric_msgs::msg::EpsInfo eps_info_msg;
  ioniq_electric_msgs::msg::AccInfo acc_info_msg;
  ioniq_electric_msgs::msg::SpdInfo spd_info_msg;
  ioniq_electric_msgs::msg::ImuInfo imu_info_msg;
  ioniq_electric_msgs::msg::RadInfo rad_info_msg;
  ioniq_electric_msgs::msg::AdditionalSig additional_sig_msg;


  uint8_t byte_temp[8];
  switch (msg->id)
  {
    case EpsInfo::ID:
      eps_info_received_time_ = this->now();
      for(uint i=0;i<8;i++)
      {
      byte_temp[i] = msg->data[i];
      }
      eps_info_entity_.update_bytes(byte_temp);
      eps_info_entity_.Parse();

      eps_info_msg.header = header;
      eps_info_msg.eps_en_status = eps_info_entity_.eps_en_status_;
      eps_info_msg.eps_control_board_status = eps_info_entity_.eps_control_board_status_;
      eps_info_msg.eps_control_status = eps_info_entity_.eps_control_status_;
      eps_info_msg.eps_user_can_err = eps_info_entity_.eps_user_can_err_;
      eps_info_msg.eps_err = eps_info_entity_.eps_err_;
      eps_info_msg.eps_veh_can_err = eps_info_entity_.eps_veh_can_err_;
      eps_info_msg.eps_sas_err = eps_info_entity_.eps_sas_err_;
      eps_info_msg.override_ignore_status = eps_info_entity_.override_ignore_status_;
      eps_info_msg.override_status = eps_info_entity_.override_status_;
      eps_info_msg.str_ang = eps_info_entity_.str_ang_;
      eps_info_msg.str_drv_tq = eps_info_entity_.str_drv_tq_;
      eps_info_msg.str_out_tq = eps_info_entity_.str_out_tq_;
      eps_info_msg.eps_alive_cnt = eps_info_entity_.eps_alive_cnt_;

      eps_info_ptr_ = std::make_shared<ioniq_electric_msgs::msg::EpsInfo>(eps_info_msg);
    break;
    

    case AccInfo::ID:
      acc_info_received_time_ = this->now();
    
      for(uint i=0;i<8;i++)
      {
      byte_temp[i] = msg->data[i];
      }
      acc_info_entity_.update_bytes(byte_temp);
      acc_info_entity_.Parse();

      acc_info_msg.header = header;
      acc_info_msg.acc_en_status = acc_info_entity_.acc_en_status_;
      acc_info_msg.acc_control_board_status = acc_info_entity_.acc_control_board_status_;
      acc_info_msg.acc_control_status = acc_info_entity_.acc_control_status_;
      acc_info_msg.acc_user_can_err = acc_info_entity_.acc_user_can_err_;
      acc_info_msg.acc_err = acc_info_entity_.acc_err_;
      acc_info_msg.vs = acc_info_entity_.vs_;
      acc_info_msg.long_accel = acc_info_entity_.long_accel_;
      acc_info_msg.hazard_en = acc_info_entity_.hazard_en_;
      acc_info_msg.turn_left_en = acc_info_entity_.turn_left_en_;
      acc_info_msg.turn_right_en = acc_info_entity_.turn_right_en_;
      acc_info_msg.acc_veh_err = acc_info_entity_.acc_veh_err_;
      acc_info_msg.g_sel_disp = acc_info_entity_.g_sel_disp_;
      acc_info_msg.acc_alive_cnt = acc_info_entity_.acc_alive_cnt_;

      acc_info_ptr_ = std::make_shared<ioniq_electric_msgs::msg::AccInfo>(acc_info_msg);
    break;
    

    case SpdInfo::ID:
      spd_info_received_time_ = this->now();
      
      for(uint i=0;i<8;i++)
      {
      byte_temp[i] = msg->data[i];
      }
      spd_info_entity_.update_bytes(byte_temp);
      spd_info_entity_.Parse();

      spd_info_msg.header = header;
      spd_info_msg.wheel_spd_fr = spd_info_entity_.wheel_spd_fr_;
      spd_info_msg.wheel_spd_fl = spd_info_entity_.wheel_spd_fl_;
      spd_info_msg.wheel_spd_rr = spd_info_entity_.wheel_spd_rr_;
      spd_info_msg.wheel_spd_rl = spd_info_entity_.wheel_spd_rl_;

      spd_info_ptr_ = std::make_shared<ioniq_electric_msgs::msg::SpdInfo>(spd_info_msg);
    break;
    

    case ImuInfo::ID:
      imu_info_received_time_ = this->now();
      
      for(uint i=0;i<8;i++)
      {
      byte_temp[i] = msg->data[i];
      }
      imu_info_entity_.update_bytes(byte_temp);
      imu_info_entity_.Parse();

      imu_info_msg.header = header;
      imu_info_msg.lat_accel = imu_info_entity_.lat_accel_;
      imu_info_msg.yaw_rate = imu_info_entity_.yaw_rate_;
      imu_info_msg.brk_cylinder = imu_info_entity_.brk_cylinder_;

      imu_info_ptr_ = std::make_shared<ioniq_electric_msgs::msg::ImuInfo>(imu_info_msg);
    break;
    

    case RadInfo::ID:
      rad_info_received_time_ = this->now();
      
      for(uint i=0;i<8;i++)
      {
      byte_temp[i] = msg->data[i];
      }
      rad_info_entity_.update_bytes(byte_temp);
      rad_info_entity_.Parse();

      rad_info_msg.header = header;
      rad_info_msg.rad_obj_rel_spd = rad_info_entity_.rad_obj_rel_spd_;
      rad_info_msg.rad_obj_dist = rad_info_entity_.rad_obj_dist_;
      rad_info_msg.rad_obj_lat_pos = rad_info_entity_.rad_obj_lat_pos_;
      rad_info_msg.rad_obj_state = rad_info_entity_.rad_obj_state_;

      rad_info_ptr_ = std::make_shared<ioniq_electric_msgs::msg::RadInfo>(rad_info_msg);
    break;
    

    case AdditionalSig::ID:
      additional_sig_received_time_ = this->now();
      
      for(uint i=0;i<8;i++)
      {
      byte_temp[i] = msg->data[i];
      }
      additional_sig_entity_.update_bytes(byte_temp);
      additional_sig_entity_.Parse();

      additional_sig_msg.header = header;
      additional_sig_msg.accelerator_pedal_position = additional_sig_entity_.accelerator_pedal_position_;
      additional_sig_msg.steering_wheel_angle_rate = additional_sig_entity_.steering_wheel_angle_rate_;
      additional_sig_msg.brake_act_signal = additional_sig_entity_.brake_act_signal_;

      additional_sig_ptr_ = std::make_shared<ioniq_electric_msgs::msg::AdditionalSig>(additional_sig_msg);
    break;
    

  default:
    break;
  }
}

void ReportParser::timerCallback()
{
    if (!is_publish_) return;

    const rclcpp::Time current_time = this->now();

    checkAndPublishMessage(eps_info_received_time_, eps_info_ptr_, eps_info_pub_, "eps_info");
    checkAndPublishMessage(acc_info_received_time_, acc_info_ptr_, acc_info_pub_, "acc_info");
    checkAndPublishMessage(spd_info_received_time_, spd_info_ptr_, spd_info_pub_, "spd_info");
    checkAndPublishMessage(imu_info_received_time_, imu_info_ptr_, imu_info_pub_, "imu_info");
    checkAndPublishMessage(rad_info_received_time_, rad_info_ptr_, rad_info_pub_, "rad_info");
    checkAndPublishMessage(additional_sig_received_time_, additional_sig_ptr_, additional_sig_pub_, "additional_sig");
}

template <typename MsgType>
void ReportParser::checkAndPublishMessage(
    const rclcpp::Time &received_time, 
    const std::shared_ptr<const MsgType> &msg_ptr, 
    const std::shared_ptr<rclcpp::Publisher<MsgType>> &pub,
    const std::string &msg_name)
{
    const rclcpp::Time current_time = this->now();
    const double report_delta_time_ms = (current_time - received_time).seconds() * 1000.0;

    // Log timeout error
    if (report_delta_time_ms > param_.report_timeout_ms)
    {
        RCLCPP_ERROR_THROTTLE(
            get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
            "%s report timeout = %f ms.", msg_name.c_str(), report_delta_time_ms);
    }

    // Publish if pointer is valid
    if (msg_ptr != nullptr)
    {
        pub->publish(*msg_ptr);
    }
}

} // namespace report_parser
} // namespace ioniq_electric_interface