#pragma once
#include <ioniq_electric_interface/Byte.hpp>

class CtrlA {
public:
	static  int32_t ID;

	CtrlA();

  	void UpdateData(bool eps_en, bool eps_override_ignore, int eps_speed, bool acc_en, bool aeb_en, int aliv_cnt, double aeb_decel_value, bool acc_override_ignore, int gear_sel, int turn_signal);

  	void Reset();
  
  	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'eps_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_eps_en(bool eps_en);

  // config detail: {'bit': 2, 'is_signed_var': False, 'len': 1, 'name': 'eps_override_ignore', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_eps_override_ignore(bool eps_override_ignore);

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'eps_speed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[10|250]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_eps_speed(int eps_speed);

  // config detail: {'bit': 16, 'is_signed_var': False, 'len': 1, 'name': 'acc_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_acc_en(bool acc_en);

  // config detail: {'bit': 22, 'is_signed_var': False, 'len': 1, 'name': 'aeb_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_aeb_en(bool aeb_en);

  // config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'aliv_cnt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_aliv_cnt(int aliv_cnt);

  // config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'aeb_decel_value', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2.55]', 'physical_unit': 'g', 'precision': 0.01, 'type': 'double'}
  void set_p_aeb_decel_value(double aeb_decel_value);

  // config detail: {'bit': 3, 'is_signed_var': False, 'len': 1, 'name': 'acc_override_ignore', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_acc_override_ignore(bool acc_override_ignore);

  // config detail: {'bit': 44, 'is_signed_var': False, 'len': 4, 'name': 'gear_sel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_gear_sel(int gear_sel);

  // config detail: {'bit': 40, 'is_signed_var': False, 'len': 3, 'name': 'turn_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_turn_signal(int turn_signal);

private:
	uint8_t data[8];
};



