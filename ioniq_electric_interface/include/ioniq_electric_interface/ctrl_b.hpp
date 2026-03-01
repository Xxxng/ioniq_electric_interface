#pragma once
#include <ioniq_electric_interface/Byte.hpp>

class CtrlB {
public:
	static  int32_t ID;

	CtrlB();

  	void UpdateData(double eps_cmd, double acc_cmd);

  	void Reset();
  
  	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'is_signed_var': True, 'len': 16, 'name': 'eps_cmd', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
  void set_p_eps_cmd(double eps_cmd);

  // config detail: {'bit': 24, 'is_signed_var': False, 'len': 16, 'name': 'acc_cmd', 'offset': -10.23, 'order': 'intel', 'physical_range': '[-3|1]', 'physical_unit': 'm/s', 'precision': 0.01, 'type': 'double'}
  void set_p_acc_cmd(double acc_cmd);

private:
	uint8_t data[8];
};



