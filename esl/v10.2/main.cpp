#include <systemc>
#include "generator.hpp"
#include "memory.hpp"

using namespace sc_core;
using namespace tlm;

int sc_main(int argc, char* argv[])
{
	//sc_mutex mtx1;
	//memory mem ("memory_u", &mtx1);
	//generator gen("generator_u", &mtx1);
	memory mem ("memory_u");
	generator gen("generator_u");
	gen.isoc(mem.tsoc);

	sc_start(200, SC_NS);
    return 0;
}
