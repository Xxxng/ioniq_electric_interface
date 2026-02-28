#include <ioniq_electric_interface/additional_sig.hpp>


AdditionalSig::AdditionalSig() {}

void AdditionalSig::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void AdditionalSig::Parse() {
  accelerator_pedal_position_ = acceleratorpedalposition();
  steering_wheel_angle_rate_ = steeringwheelanglerate();
  brake_act_signal_ = brakeactsignal();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'accelerator_pedal_position', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|99.603]', 'physical_unit': '%', 'precision': 0.3906, 'type': 'double'}
double AdditionalSig::acceleratorpedalposition() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.390600;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'steering_wheel_angle_rate', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1016]', 'physical_unit': 'deg/s', 'precision': 4.0, 'type': 'double'}
double AdditionalSig::steeringwheelanglerate() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 4.000000;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 2, 'name': 'brake_act_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int AdditionalSig::brakeactsignal() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

