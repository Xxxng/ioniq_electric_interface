#include <ioniq_electric_interface/rad_info.hpp>


RadInfo::RadInfo() {}

void RadInfo::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void RadInfo::Parse() {
  rad_obj_rel_spd_ = radobjrelspd();
  rad_obj_dist_ = radobjdist();
  rad_obj_lat_pos_ = radobjlatpos();
  rad_obj_state_ = radobjstate();
}


// config detail: {'bit': 48, 'is_signed_var': False, 'len': 16, 'name': 'rad_obj_rel_spd', 'offset': -170.0, 'order': 'intel', 'physical_range': '[-170|239.5]', 'physical_unit': 'm/s', 'precision': 0.1, 'type': 'double'}
double RadInfo::radobjrelspd() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 6));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -170.000000;
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 16, 'name': 'rad_obj_dist', 'offset': -10.0, 'order': 'intel', 'physical_range': '[0|204.7]', 'physical_unit': 'm', 'precision': 0.2, 'type': 'double'}
double RadInfo::radobjdist() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 4));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.200000 + -10.000000;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 16, 'name': 'rad_obj_lat_pos', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|31.1]', 'physical_unit': 'm', 'precision': 0.1, 'type': 'double'}
double RadInfo::radobjlatpos() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 2));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -20.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'rad_obj_state', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int RadInfo::radobjstate() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

