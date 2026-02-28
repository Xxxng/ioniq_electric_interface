#include <ioniq_electric_interface/report_parser.hpp>
#include <rclcpp/rclcpp.hpp>
#include <memory>

int main(int argc, char ** argv)
{ 
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ioniq_electric_interface::report_parser::ReportParser>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}