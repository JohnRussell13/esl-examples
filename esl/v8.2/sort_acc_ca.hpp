#define SC_INCLUDE_FX
// Cycle accurate model of sort accelerator

#ifndef _SORT_ACC_CA_HPP_
#define _SORT_ACC_CA_HPP_

#include <systemc.h>
#include "sort_ifs.hpp"

class sort_acc_ca_calculate;

class sort_acc_ca :
	public sc_core::sc_channel,
	public sort_write_if,
	public sort_read_if
{
public:
	SC_HAS_PROCESS(sort_acc_ca);

	sort_acc_ca(sc_core::sc_module_name name);

	void write(const std::vector<sc_dt::sc_fixed<16,5> >& data);
	void read(std::vector<sc_dt::sc_fixed<16,5> >& data);

	sc_core::sc_clock clk;
	sc_core::sc_signal< bool > rst;

	sc_core::sc_signal< sc_dt::sc_logic > in_tready;
	sc_core::sc_signal< sc_dt::sc_fixed<16,5> > in_tdata;
	sc_core::sc_signal< sc_dt::sc_logic > in_tlast;
	sc_core::sc_signal< sc_dt::sc_logic > in_tvalid;

	sc_core::sc_signal< sc_dt::sc_logic > out_tready;
	sc_core::sc_signal< sc_dt::sc_fixed<16,5> > out_tdata;
	sc_core::sc_signal< sc_dt::sc_logic > out_tlast;
	sc_core::sc_signal< sc_dt::sc_logic > out_tvalid;


	friend void sc_trace(sc_core::sc_trace_file*, const sort_acc_ca&, const std::string& name);
protected:
	sort_acc_ca_calculate* core;
};

#endif
