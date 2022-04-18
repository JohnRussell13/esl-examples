#include <systemc>
#include "generator.hpp"
#include "memory.hpp"

using namespace sc_core;
using namespace tlm;

int sc_main(int argc, char* argv[])
{
	memory mem ("memory_u");
	generator gen("generator_u");
	gen.isoc(mem.tsoc);

	sc_start(200, SC_NS);
    return 0;
}
