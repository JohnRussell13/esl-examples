#define SC_INCLUDE_FX
#include "tb_sort_acc.hpp"
#include "sort_gen_check.hpp"
#include "sort_acc_tlm.hpp"
#include "sort_acc_ca.hpp"

using namespace std;
using namespace sc_core;

tb_sort_acc::tb_sort_acc(sc_module_name name, const std::string& cfg) :
  sc_module(name), gc(NULL), acc(NULL), acc_ca(NULL)
{
  gc = new sort_gen_check("m_gen_check");
  if (cfg == "ca")
  {
	  acc_ca = new sort_acc_ca("m_sort_acc");
	  gc->wr_port(*acc_ca);
	  gc->rd_port(*acc_ca);
  }
  else
  {
	  acc = new sort_acc_tlm("m_sort_acc");
	  gc->wr_port(*acc);
	  gc->rd_port(*acc);
  }
}


void sc_trace(sc_core::sc_trace_file* tf, const tb_sort_acc& obj, const std::string& name)
{
  if (obj.acc_ca != NULL)
	sc_trace(tf, *(obj.acc_ca), name);
}
