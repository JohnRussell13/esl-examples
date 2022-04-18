#define SC_INCLUDE_FX
#ifndef _SORT_ACC_TLM_HPP_
#define _SORT_ACC_TLM_HPP_

#include <systemc>
#include "sort_ifs.hpp"

class sort_acc_tlm :
	public sc_core::sc_channel,
	public sort_write_if,
	public sort_read_if
{
public:
	SC_HAS_PROCESS(sort_acc_tlm);

	sort_acc_tlm(sc_core::sc_module_name);
	void write(const std::vector<sc_dt::sc_fixed<16,5> >& data);
	void read(std::vector<sc_dt::sc_fixed<16,5> >& data);
	void calculate();
protected:
	std::vector<sc_dt::sc_fixed<16,5> > x_tlm;
	std::vector<sc_dt::sc_fixed<16,5> > y_tlm;
};

#endif
