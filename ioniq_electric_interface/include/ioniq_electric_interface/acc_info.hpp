#pragma once

#include <ioniq_electric_interface/Byte.hpp>
#include <iostream>

class AccInfo {
public:
    static const uint32_t ID = 0x711;
    AccInfo();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    bool acc_en_status_;
    int acc_control_board_status_;
    int acc_control_status_;
    bool acc_user_can_err_;
    bool acc_err_;
    int vs_;
    double long_accel_;
    bool hazard_en_;
    bool turn_left_en_;
    bool turn_right_en_;
    bool acc_veh_err_;
    int g_sel_disp_;
    int acc_alive_cnt_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'acc_en_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool accenstatus();

  // config detail: {'bit': 1, 'is_signed_var': False, 'len': 3, 'name': 'acc_control_board_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int acccontrolboardstatus();

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 4, 'name': 'acc_control_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int acccontrolstatus();

  // config detail: {'bit': 4, 'is_signed_var': False, 'len': 1, 'name': 'acc_user_can_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool accusercanerr();

  // config detail: {'bit': 7, 'is_signed_var': False, 'len': 1, 'name': 'acc_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool accerr();

  // config detail: {'bit': 16, 'is_signed_var': False, 'len': 8, 'name': 'vs', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'km/h', 'precision': 1.0, 'type': 'int'}
  int vs();

  // config detail: {'bit': 32, 'is_signed_var': False, 'len': 11, 'name': 'long_accel', 'offset': -10.23, 'order': 'intel', 'physical_range': '[-10.23|10.24]', 'physical_unit': 'm/s^2', 'precision': 0.01, 'type': 'double'}
  double longaccel();

  // config detail: {'bit': 49, 'is_signed_var': False, 'len': 1, 'name': 'hazard_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool hazarden();

  // config detail: {'bit': 50, 'is_signed_var': False, 'len': 1, 'name': 'turn_left_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool turnleften();

  // config detail: {'bit': 48, 'is_signed_var': False, 'len': 1, 'name': 'turn_right_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool turnrighten();

  // config detail: {'bit': 6, 'is_signed_var': False, 'len': 1, 'name': 'acc_veh_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool accveherr();

  // config detail: {'bit': 52, 'is_signed_var': False, 'len': 4, 'name': 'g_sel_disp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int gseldisp();

  // config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'acc_alive_cnt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int accalivecnt();
};



