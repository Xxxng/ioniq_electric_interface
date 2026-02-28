#include <ioniq_electric_interface/ctrl_a.hpp>

int32_t CtrlA::ID = 0x156;

// public
CtrlA::CtrlA() { Reset(); }

void CtrlA::UpdateData(bool eps_en, bool eps_override_ignore, int eps_speed, bool acc_en, bool aeb_en, int aliv_cnt, double aeb_decel_value, bool acc_override_ignore, int gear_sel, int turn_signal) {
  set_p_eps_en(eps_en);
  set_p_eps_override_ignore(eps_override_ignore);
  set_p_eps_speed(eps_speed);
  set_p_acc_en(acc_en);
  set_p_aeb_en(aeb_en);
  set_p_aliv_cnt(aliv_cnt);
  set_p_aeb_decel_value(aeb_decel_value);
  set_p_acc_override_ignore(acc_override_ignore);
  set_p_gear_sel(gear_sel);
  set_p_turn_signal(turn_signal);
}

void CtrlA::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * CtrlA::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'eps_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void CtrlA::set_p_eps_en(bool eps_en) {
  int x = eps_en;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 2, 'is_signed_var': False, 'len': 1, 'name': 'eps_override_ignore', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void CtrlA::set_p_eps_override_ignore(bool eps_override_ignore) {
  int x = eps_override_ignore;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 2, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'eps_speed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[10|250]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void CtrlA::set_p_eps_speed(int eps_speed) {
  // eps_speed = ProtocolData::BoundedValue(10, 250, eps_speed);
  int x = eps_speed;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 1, 'name': 'acc_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void CtrlA::set_p_acc_en(bool acc_en) {
  int x = acc_en;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 22, 'is_signed_var': False, 'len': 1, 'name': 'aeb_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void CtrlA::set_p_aeb_en(bool aeb_en) {
  int x = aeb_en;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 6, 1);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'aliv_cnt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void CtrlA::set_p_aliv_cnt(int aliv_cnt) {
  // aliv_cnt = ProtocolData::BoundedValue(0, 255, aliv_cnt);
  int x = aliv_cnt;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'aeb_decel_value', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2.55]', 'physical_unit': 'g', 'precision': 0.01, 'type': 'double'}
void CtrlA::set_p_aeb_decel_value(double aeb_decel_value) {
  // aeb_decel_value = ProtocolData::BoundedValue(0.0, 2.55, aeb_decel_value);
  int x = aeb_decel_value / 0.010000;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[6] += to_set.return_byte_t();
  
}

// config detail: {'bit': 3, 'is_signed_var': False, 'len': 1, 'name': 'acc_override_ignore', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void CtrlA::set_p_acc_override_ignore(bool acc_override_ignore) {
  int x = acc_override_ignore;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 3, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 44, 'is_signed_var': False, 'len': 4, 'name': 'gear_sel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void CtrlA::set_p_gear_sel(int gear_sel) {
  // gear_sel = ProtocolData::BoundedValue(0, 1, gear_sel);
  int x = gear_sel;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 4, 4);
  data[5] += to_set.return_byte_t();
  
}

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 3, 'name': 'turn_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void CtrlA::set_p_turn_signal(int turn_signal) {
  // turn_signal = ProtocolData::BoundedValue(0, 1, turn_signal);
  int x = turn_signal;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 3);
  data[5] += to_set.return_byte_t();
  
}


