#include <ioniq_electric_interface/control_command.hpp>
#include <rclcpp/rclcpp.hpp>
#include <memory>

int main(int argc, char ** argv)
{ 
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ioniq_electric_interface::control_command::ControlCommand>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}