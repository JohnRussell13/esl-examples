#ifndef _SORT_ACC_CA_CALCULATE_HPP_
#define _SORT_ACC_CA_CALCULATE_HPP_

#include <systemc>

SC_MODULE(sort_acc_ca_calculate)
{
public:
	SC_HAS_PROCESS(sort_acc_ca_calculate);

	sort_acc_ca_calculate(sc_core::sc_module_name);

	sc_core::sc_in< bool > clk;
	sc_core::sc_in< bool > rst;

	sc_core::sc_out< sc_dt::sc_logic > in_tready;
	sc_core::sc_in< sc_dt::sc_lv<16> > in_tdata;
	sc_core::sc_in< sc_dt::sc_logic > in_tlast;
	sc_core::sc_in< sc_dt::sc_logic > in_tvalid;

	sc_core::sc_in< sc_dt::sc_logic > out_tready;
	sc_core::sc_out< sc_dt::sc_lv<16> > out_tdata;
	sc_core::sc_out< sc_dt::sc_logic > out_tlast;
	sc_core::sc_out< sc_dt::sc_logic > out_tvalid;

protected:
	void sort();
	// void wr_data();
	// void rd_data();

	typedef sc_dt::sc_int<16> num_t;
	num_t num;
	num_t nums [10000];
};

#endif
