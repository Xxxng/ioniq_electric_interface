#pragma once

#include <ioniq_electric_interface/Byte.hpp>
#include <iostream>

class EaitInfoImu {
public:
    static const uint32_t ID = 0x713;
    EaitInfoImu();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double lat_accel_;
    double yaw_rate_;
    double brk_cylinder_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': True, 'len': 16, 'name': 'lat_accel', 'offset': -10.23, 'order': 'intel', 'physical_range': '[-10.23|10.23]', 'physical_unit': 'm/s^2', 'precision': 0.01, 'type': 'double'}
  double lataccel();

  // config detail: {'bit': 24, 'is_signed_var': True, 'len': 16, 'name': 'yaw_rate', 'offset': -40.95, 'order': 'intel', 'physical_range': '[-40.95|40.94]', 'physical_unit': 'deg/s', 'precision': 0.01, 'type': 'double'}
  double yawrate();

  // config detail: {'bit': 48, 'is_signed_var': False, 'len': 16, 'name': 'brk_cylinder', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|409.4]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
  double brkcylinder();
};



