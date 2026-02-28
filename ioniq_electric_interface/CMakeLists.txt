cmake_minimum_required(VERSION 3.5)
project(ioniq_electric_interface)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

ament_auto_add_executable(${PROJECT_NAME}_control_command_node
  src/ctrl_a.cc
  src/ctrl_b.cc
  src/vector_independent_sig_msg.cc
  src/Byte.cc
  src/control_command.cpp
  src/control_command_node.cpp
)

ament_auto_add_executable(${PROJECT_NAME}_report_parser_node
  src/eps_info.cc
  src/acc_info.cc
  src/spd_info.cc
  src/eait_info_imu.cc
  src/rad_info.cc
  src/additional_sig.cc

  src/Byte.cc
  src/report_parser.cpp
  src/report_parser_node.cpp
)

ament_auto_add_executable(${PROJECT_NAME}_control_converter_node
  src/control_converter.cpp
  src/control_converter_node.cpp
)

ament_auto_add_executable(${PROJECT_NAME}_report_converter_node
  src/report_converter.cpp
  src/report_converter_node.cpp
)

# install
ament_auto_package(
  INSTALL_TO_SHARE
  launch
  # config
)