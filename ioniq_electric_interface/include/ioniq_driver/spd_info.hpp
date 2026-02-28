#pragma once

#include <ioniq_electric_interface/Byte.hpp>
#include <iostream>

class SpdInfo {
public:
    static const uint32_t ID = 0x712;
    SpdInfo();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double wheel_spd_fr_;
    double wheel_spd_fl_;
    double wheel_spd_rr_;
    double wheel_spd_rl_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 16, 'name': 'wheel_spd_fr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|511.96875]', 'physical_unit': '', 'precision': 0.03125, 'type': 'double'}
  double wheelspdfr();

  // config detail: {'bit': 16, 'is_signed_var': False, 'len': 16, 'name': 'wheel_spd_fl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|511.96875]', 'physical_unit': '', 'precision': 0.03125, 'type': 'double'}
  double wheelspdfl();

  // config detail: {'bit': 32, 'is_signed_var': False, 'len': 16, 'name': 'wheel_spd_rr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|511.96875]', 'physical_unit': '', 'precision': 0.03125, 'type': 'double'}
  double wheelspdrr();

  // config detail: {'bit': 48, 'is_signed_var': False, 'len': 16, 'name': 'wheel_spd_rl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|511.96875]', 'physical_unit': '', 'precision': 0.03125, 'type': 'double'}
  double wheelspdrl();
};



