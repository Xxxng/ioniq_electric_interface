#include <ioniq_electric_interface/ctrl_b.hpp>

int32_t CtrlB::ID = 0x157;

// public
CtrlB::CtrlB() { Reset(); }

void CtrlB::UpdateData(double eps_cmd, double acc_cmd) {
  set_p_eps_cmd(eps_cmd);
  set_p_acc_cmd(acc_cmd);
}

void CtrlB::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * CtrlB::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'is_signed_var': True, 'len': 16, 'name': 'eps_cmd', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
void CtrlB::set_p_eps_cmd(double eps_cmd) {
  // eps_cmd = ProtocolData::BoundedValue(-500.0, 500.0, eps_cmd);
  int x = eps_cmd / 0.100000;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[0] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 8);
  data[1] += to_set1.return_byte_t();
}

// config detail: {'bit': 24, 'is_signed_var': False, 'len': 16, 'name': 'acc_cmd', 'offset': -10.23, 'order': 'intel', 'physical_range': '[-3|1]', 'physical_unit': 'm/s', 'precision': 0.01, 'type': 'double'}
void CtrlB::set_p_acc_cmd(double acc_cmd) {
  // acc_cmd = ProtocolData::BoundedValue(-3.0, 1.0, acc_cmd);
  int x = (acc_cmd - -10.230000) / 0.010000;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[3] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 8);
  data[4] += to_set1.return_byte_t();
}


