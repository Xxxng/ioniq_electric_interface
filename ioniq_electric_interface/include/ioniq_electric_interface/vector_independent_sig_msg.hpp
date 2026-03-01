#pragma once
#include <ioniq_electric_interface/Byte.hpp>

class VectorIndependentSigMsg {
public:
	static  int32_t ID;

	VectorIndependentSigMsg();

  	void UpdateData(bool curise_btn, bool cruise_cancle);

  	void Reset();
  
  	uint8_t *get_data();


private:
	
  // config detail: {'bit': 15, 'is_signed_var': False, 'len': 1, 'name': 'curise_btn', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_curise_btn(bool curise_btn);

  // config detail: {'bit': 14, 'is_signed_var': False, 'len': 1, 'name': 'cruise_cancle', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_cruise_cancle(bool cruise_cancle);

private:
	uint8_t data[8];
};



