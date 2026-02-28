#include <ioniq_electric_interface/eps_info.hpp>


EpsInfo::EpsInfo() {}

void EpsInfo::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void EpsInfo::Parse() {
  eps_en_status_ = epsenstatus();
  eps_control_board_status_ = epscontrolboardstatus();
  eps_control_status_ = epscontrolstatus();
  eps_user_can_err_ = epsusercanerr();
  eps_err_ = epserr();
  eps_veh_can_err_ = epsvehcanerr();
  eps_sas_err_ = epssaserr();
  override_ignore_status_ = overrideignorestatus();
  override_status_ = overridestatus();
  str_ang_ = strang();
  str_drv_tq_ = strdrvtq();
  str_out_tq_ = strouttq();
  eps_alive_cnt_ = epsalivecnt();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'eps_en_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool EpsInfo::epsenstatus() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 1, 'is_signed_var': False, 'len': 3, 'name': 'eps_control_board_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int EpsInfo::epscontrolboardstatus() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(1, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 4, 'name': 'eps_control_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int EpsInfo::epscontrolstatus() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 4, 'is_signed_var': False, 'len': 1, 'name': 'eps_user_can_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool EpsInfo::epsusercanerr() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 5, 'is_signed_var': False, 'len': 1, 'name': 'eps_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool EpsInfo::epserr() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(5, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 6, 'is_signed_var': False, 'len': 1, 'name': 'eps_veh_can_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool EpsInfo::epsvehcanerr() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(6, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 7, 'is_signed_var': False, 'len': 1, 'name': 'eps_sas_err', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool EpsInfo::epssaserr() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(7, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 12, 'is_signed_var': False, 'len': 1, 'name': 'override_ignore_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool EpsInfo::overrideignorestatus() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(4, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 13, 'is_signed_var': False, 'len': 1, 'name': 'override_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool EpsInfo::overridestatus() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(5, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': True, 'len': 16, 'name': 'str_ang', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
double EpsInfo::strang() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 2));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 12, 'name': 'str_drv_tq', 'offset': -20.48, 'order': 'intel', 'physical_range': '[-20.48|20.47]', 'physical_unit': '', 'precision': 0.01, 'type': 'double'}
double EpsInfo::strdrvtq() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 4);

  Byte t1(*(bytes + 4));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000 + -20.480000;
  return ret;
}

// config detail: {'bit': 44, 'is_signed_var': False, 'len': 12, 'name': 'str_out_tq', 'offset': -204.8, 'order': 'intel', 'physical_range': '[-204.8|204.7]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
double EpsInfo::strouttq() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 5));
  int32_t t = t1.get_byte(4, 4);
  x <<= 4;
  x |= t;

  double ret = x * 0.100000 + -204.800000;
  return ret;
}

// config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'eps_alive_cnt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int EpsInfo::epsalivecnt() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

