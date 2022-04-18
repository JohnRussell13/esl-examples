#define SC_INCLUDE_FX
#include <systemc>
#include <string>
#include "tb_sort_acc.hpp"

using namespace sc_core;

int sc_main(int argc, char* argv[])
{
    //type of model: tlm vs ca
	std::string cfg("ca");
	std::string cfgtmp;
	if (argc > 1)
		cfgtmp = argv[1];
	if (cfgtmp == "ca")
		cfg = "ca";

	tb_sort_acc tb("TB", cfg);

	sc_trace_file *wf = sc_create_vcd_trace_file("sort");
	sc_trace(wf, tb, "clk");

	sc_start(20, SC_MS);

	sc_close_vcd_trace_file(wf);

    return 0;
}
