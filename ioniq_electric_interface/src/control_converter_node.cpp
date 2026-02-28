#include <ioniq_electric_interface/control_converter.hpp>

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ioniq_electric_interface::control_converter::ControlConverter>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}