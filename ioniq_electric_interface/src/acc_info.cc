#include <ioniq_electric_interface/acc_info.hpp>


AccInfo::AccInfo() {}

void AccInfo::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void AccInfo::Parse() {
  acc_en_status_ = accenstatus();
  acc_control_board_status_ = acccontrolboardstatus();
  acc_control_status_ = acccontrolstatus();
  acc_user_can_err_ = accusercanerr();
  acc_err_ = accerr();
  vs_ = vs();
  long_accel_ = longaccel();
  hazard_en_ = hazarden();
  turn_left_en_ = turnleften();
  turn_right_en_ = turnrighten();
  acc_veh_err_ = accveherr();
  g_sel_disp_ = gseldisp();
  acc_alive_cnt_ = accalivecnt();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'acc_en_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool AccInfo::accenstatus() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 1, 'is_signed_var': False, 'len': 3, 'name': 'acc_control_board_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int AccInfo::acccontrolboardstatus() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(1, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 4, 'name': 'acc_control_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int AccInfo::acccontrolstatus() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 4, 'is_signed_var': False, 'len': 1, 'name': 'acc_user_can_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool AccInfo::accusercanerr() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 7, 'is_signed_var': False, 'len': 1, 'name': 'acc_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool AccInfo::accerr() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(7, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 8, 'name': 'vs', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'km/h', 'precision': 1.0, 'type': 'int'}
int AccInfo::vs() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 11, 'name': 'long_accel', 'offset': -10.23, 'order': 'intel', 'physical_range': '[-10.23|10.24]', 'physical_unit': 'm/s^2', 'precision': 0.01, 'type': 'double'}
double AccInfo::longaccel() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 3);

  Byte t1(*(bytes + 4));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000 + -10.230000;
  return ret;
}

// config detail: {'bit': 49, 'is_signed_var': False, 'len': 1, 'name': 'hazard_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool AccInfo::hazarden() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(1, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 50, 'is_signed_var': False, 'len': 1, 'name': 'turn_left_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool AccInfo::turnleften() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(2, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 1, 'name': 'turn_right_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool AccInfo::turnrighten() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 6, 'is_signed_var': False, 'len': 1, 'name': 'acc_veh_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool AccInfo::accveherr() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(6, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 52, 'is_signed_var': False, 'len': 4, 'name': 'g_sel_disp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int AccInfo::gseldisp() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'acc_alive_cnt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int AccInfo::accalivecnt() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

