#define SC_INCLUDE_FX
#ifndef _TB_SORT_ACC_HPP_
#define _TB_SORT_ACC_HPP_

#include <systemc>

class sort_gen_check;
class sort_acc_tlm;
class sort_acc_ca;

SC_MODULE(tb_sort_acc)
{
public:
	tb_sort_acc(sc_core::sc_module_name, const std::string& cfg);

	friend void sc_trace(sc_core::sc_trace_file*, const tb_sort_acc&, const std::string& name);

protected:
	sort_gen_check* gc;
	sort_acc_tlm* acc;
	sort_acc_ca* acc_ca;
};

#endif
