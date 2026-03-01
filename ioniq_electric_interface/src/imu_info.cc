#include <ioniq_electric_interface/imu_info.hpp>


ImuInfo::ImuInfo() {}

void ImuInfo::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void ImuInfo::Parse() {
  lat_accel_ = lataccel();
  yaw_rate_ = yawrate();
  brk_cylinder_ = brkcylinder();
}


// config detail: {'bit': 0, 'is_signed_var': True, 'len': 16, 'name': 'lat_accel', 'offset': -10.23, 'order': 'intel', 'physical_range': '[-10.23|10.23]', 'physical_unit': 'm/s^2', 'precision': 0.01, 'type': 'double'}
double ImuInfo::lataccel() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 0));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.010000 + -10.230000;
  return ret;
}

// config detail: {'bit': 24, 'is_signed_var': True, 'len': 16, 'name': 'yaw_rate', 'offset': -40.95, 'order': 'intel', 'physical_range': '[-40.95|40.94]', 'physical_unit': 'deg/s', 'precision': 0.01, 'type': 'double'}
double ImuInfo::yawrate() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 3));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.010000 + -40.950000;
  return ret;
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 16, 'name': 'brk_cylinder', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|409.4]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
double ImuInfo::brkcylinder() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 6));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

