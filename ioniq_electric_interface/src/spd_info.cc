#include <ioniq_electric_interface/spd_info.hpp>


SpdInfo::SpdInfo() {}

void SpdInfo::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void SpdInfo::Parse() {
  wheel_spd_fr_ = wheelspdfr();
  wheel_spd_fl_ = wheelspdfl();
  wheel_spd_rr_ = wheelspdrr();
  wheel_spd_rl_ = wheelspdrl();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 16, 'name': 'wheel_spd_fr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|511.96875]', 'physical_unit': '', 'precision': 0.03125, 'type': 'double'}
double SpdInfo::wheelspdfr() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 0));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.031250;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 16, 'name': 'wheel_spd_fl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|511.96875]', 'physical_unit': '', 'precision': 0.03125, 'type': 'double'}
double SpdInfo::wheelspdfl() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 2));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.031250;
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 16, 'name': 'wheel_spd_rr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|511.96875]', 'physical_unit': '', 'precision': 0.03125, 'type': 'double'}
double SpdInfo::wheelspdrr() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 4));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.031250;
  return ret;
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 16, 'name': 'wheel_spd_rl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|511.96875]', 'physical_unit': '', 'precision': 0.03125, 'type': 'double'}
double SpdInfo::wheelspdrl() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 6));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.031250;
  return ret;
}

