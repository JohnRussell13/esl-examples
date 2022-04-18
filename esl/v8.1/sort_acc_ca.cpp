#include "sort_acc_ca.hpp"
#ifdef COSIM
#include "sort_acc_ca_calculate_rtl.hpp"
#else
#include "sort_acc_ca_calculate.hpp"
#endif

using namespace sc_core;
using namespace sc_dt;
using namespace std;

sort_acc_ca::sort_acc_ca(sc_module_name name) :
	sc_module(name),
	clk("m_clk", 100, SC_NS, 0.4, 5, SC_NS, true),
	rst("rst"),
	in_tready("in_tready"),
	in_tdata("in_tdata"),
	in_tlast("in_tlast"),
	in_tvalid("in_tvalid"),
	out_tready("out_tready"),
	out_tdata("out_tdata"),
	out_tlast("out_tlast"),
	out_tvalid("out_tvalid")
{
#ifndef COSIM
	core = new sort_acc_ca_calculate("core");

	core->clk(clk);
	core->in_tready(in_tready);
	core->in_tdata(in_tdata);
	core->in_tlast(in_tlast);
	core->in_tvalid(in_tvalid);
	core->out_tready(out_tready);
	core->out_tdata(out_tdata);
	core->out_tlast(out_tlast);
	core->out_tvalid(out_tvalid);
	core->rst(rst);
#else
	core = new sort_acc_ca_calculate("core", "sort_acc_ca_calculate");

	core->ap_clk(clk);
	core->in_r_TREADY(in_tready);
	core->in_r_TDATA(in_tdata);
	core->in_r_TLAST(in_tlast);
	core->in_r_TVALID(in_tvalid);
	core->out_r_TREADY(out_tready);
	core->out_r_TDATA(out_tdata);
	core->out_r_TLAST(out_tlast);
	core->out_r_TVALID(out_tvalid);
	core->ap_rst_n(rst);
#endif
}


void sort_acc_ca::write(const int& data)
{
	rst.write(false);
	out_tready.write(SC_LOGIC_0);
	in_tvalid.write(SC_LOGIC_0);
	in_tlast.write(SC_LOGIC_0);

	for (int i = 0; i != 10; ++i)
		wait(clk.negedge_event());

		sc_lv<16> v(data);
		in_tdata = v;
		in_tvalid = SC_LOGIC_1;
			in_tlast = SC_LOGIC_1;
		while(true)
		{
			wait(clk.negedge_event());
			if (in_tready == SC_LOGIC_1) break;
		}

	cout << "Transaction translated.\n";
	in_tvalid = SC_LOGIC_0;
	in_tlast = SC_LOGIC_0;
}

void sort_acc_ca::read(std::vector<int>& data)
{
	rst.write(false);
	data.clear();
	wait(clk.negedge_event());
	out_tready = SC_LOGIC_1;

	while(1)
	{
		wait(clk.negedge_event());
		if (out_tvalid == SC_LOGIC_1)
		{
			sc_lv<16> v = out_tdata;
			data.push_back(v.to_int());
			if (out_tlast == SC_LOGIC_1)
				break;
		}
	}

	wait(clk.negedge_event());
	out_tready = SC_LOGIC_0;
}

void sc_trace(sc_core::sc_trace_file* tf, const sort_acc_ca& obj, const std::string& name)
{
	sc_trace(tf, obj.clk, name + ".clk");
	sc_trace(tf, obj.in_tready, name + ".in_tready");
	sc_trace(tf, obj.in_tdata, name + ".in_tdata");
	sc_trace(tf, obj.in_tlast, name + ".in_tlast");
	sc_trace(tf, obj.in_tvalid, name + ".in_tvalid");
	sc_trace(tf, obj.out_tready, name + ".out_tready");
	sc_trace(tf, obj.out_tdata, name + ".out_tdata");
	sc_trace(tf, obj.out_tlast, name + ".out_tlast");
	sc_trace(tf, obj.out_tvalid, name + ".out_tvalid");
}
