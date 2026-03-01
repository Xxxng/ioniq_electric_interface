#pragma once

#include <ioniq_electric_interface/Byte.hpp>
#include <iostream>

class EpsInfo {
public:
    static const uint32_t ID = 0x710;
    EpsInfo();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    bool eps_en_status_;
    int eps_control_board_status_;
    int eps_control_status_;
    bool eps_user_can_err_;
    bool eps_err_;
    bool eps_veh_can_err_;
    bool eps_sas_err_;
    bool override_ignore_status_;
    bool override_status_;
    double str_ang_;
    double str_drv_tq_;
    double str_out_tq_;
    int eps_alive_cnt_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'eps_en_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool epsenstatus();

  // config detail: {'bit': 1, 'is_signed_var': False, 'len': 3, 'name': 'eps_control_board_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int epscontrolboardstatus();

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 4, 'name': 'eps_control_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int epscontrolstatus();

  // config detail: {'bit': 4, 'is_signed_var': False, 'len': 1, 'name': 'eps_user_can_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool epsusercanerr();

  // config detail: {'bit': 5, 'is_signed_var': False, 'len': 1, 'name': 'eps_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool epserr();

  // config detail: {'bit': 6, 'is_signed_var': False, 'len': 1, 'name': 'eps_veh_can_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool epsvehcanerr();

  // config detail: {'bit': 7, 'is_signed_var': False, 'len': 1, 'name': 'eps_sas_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool epssaserr();

  // config detail: {'bit': 12, 'is_signed_var': False, 'len': 1, 'name': 'override_ignore_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool overrideignorestatus();

  // config detail: {'bit': 13, 'is_signed_var': False, 'len': 1, 'name': 'override_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool overridestatus();

  // config detail: {'bit': 16, 'is_signed_var': True, 'len': 16, 'name': 'str_ang', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
  double strang();

  // config detail: {'bit': 32, 'is_signed_var': False, 'len': 12, 'name': 'str_drv_tq', 'offset': -20.48, 'order': 'intel', 'physical_range': '[-20.48|20.47]', 'physical_unit': '', 'precision': 0.01, 'type': 'double'}
  double strdrvtq();

  // config detail: {'bit': 44, 'is_signed_var': False, 'len': 12, 'name': 'str_out_tq', 'offset': -204.8, 'order': 'intel', 'physical_range': '[-204.8|204.7]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
  double strouttq();

  // config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'eps_alive_cnt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int epsalivecnt();
};



