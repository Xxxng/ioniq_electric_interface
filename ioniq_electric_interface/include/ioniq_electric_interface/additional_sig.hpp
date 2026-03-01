#pragma once

#include <ioniq_electric_interface/Byte.hpp>
#include <iostream>

class AdditionalSig {
public:
    static const uint32_t ID = 0x715;
    AdditionalSig();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double accelerator_pedal_position_;
    double steering_wheel_angle_rate_;
    int brake_act_signal_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'accelerator_pedal_position', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|99.603]', 'physical_unit': '%', 'precision': 0.3906, 'type': 'double'}
  double acceleratorpedalposition();

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'steering_wheel_angle_rate', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1016]', 'physical_unit': 'deg/s', 'precision': 4.0, 'type': 'double'}
  double steeringwheelanglerate();

  // config detail: {'bit': 16, 'is_signed_var': False, 'len': 2, 'name': 'brake_act_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int brakeactsignal();
};



