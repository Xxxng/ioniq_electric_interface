#pragma once

#include <ioniq_electric_interface/Byte.hpp>
#include <iostream>

class RadInfo {
public:
    static const uint32_t ID = 0x714;
    RadInfo();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double rad_obj_rel_spd_;
    double rad_obj_dist_;
    double rad_obj_lat_pos_;
    int rad_obj_state_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 48, 'is_signed_var': False, 'len': 16, 'name': 'rad_obj_rel_spd', 'offset': -170.0, 'order': 'intel', 'physical_range': '[-170|239.5]', 'physical_unit': 'm/s', 'precision': 0.1, 'type': 'double'}
  double radobjrelspd();

  // config detail: {'bit': 32, 'is_signed_var': False, 'len': 16, 'name': 'rad_obj_dist', 'offset': -10.0, 'order': 'intel', 'physical_range': '[0|204.7]', 'physical_unit': 'm', 'precision': 0.2, 'type': 'double'}
  double radobjdist();

  // config detail: {'bit': 16, 'is_signed_var': False, 'len': 16, 'name': 'rad_obj_lat_pos', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|31.1]', 'physical_unit': 'm', 'precision': 0.1, 'type': 'double'}
  double radobjlatpos();

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'rad_obj_state', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int radobjstate();
};



