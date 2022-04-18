#ifndef _SORT_GEN_CHECK_HPP_
#define _SORT_GEN_CHECK_HPP_

#include <systemc>
#include "sort_ifs.hpp"

SC_MODULE(sort_gen_check)
{
public:
	SC_HAS_PROCESS(sort_gen_check);

	sort_gen_check(sc_core::sc_module_name);

	sc_core::sc_port< sort_write_if > wr_port;
	sc_core::sc_port< sort_read_if > rd_port;
protected:
	void test();
};

#endif
