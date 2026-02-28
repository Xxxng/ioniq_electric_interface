#include <ioniq_electric_interface/vector_independent_sig_msg.hpp>

int32_t VectorIndependentSigMsg::ID = 0x20000000;

// public
VectorIndependentSigMsg::VectorIndependentSigMsg() { Reset(); }

void VectorIndependentSigMsg::UpdateData(bool curise_btn, bool cruise_cancle) {
  set_p_curise_btn(curise_btn);
  set_p_cruise_cancle(cruise_cancle);
}

void VectorIndependentSigMsg::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * VectorIndependentSigMsg::get_data()
{
  return data;
}



// config detail: {'bit': 15, 'is_signed_var': False, 'len': 1, 'name': 'curise_btn', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void VectorIndependentSigMsg::set_p_curise_btn(bool curise_btn) {
  int x = curise_btn;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 7, 1);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 14, 'is_signed_var': False, 'len': 1, 'name': 'cruise_cancle', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void VectorIndependentSigMsg::set_p_cruise_cancle(bool cruise_cancle) {
  int x = cruise_cancle;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 6, 1);
  data[1] += to_set.return_byte_t();
  
}


