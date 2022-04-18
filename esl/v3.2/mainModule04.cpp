#include <systemc>
#include "Module04.hpp"

int sc_main(int argc, char* argv[])
{

    sc_core::sc_vector<Module04> m("UUTs", 100);

	sc_start(100, sc_core::SC_NS);

	std::cout << "Simulation finished at " << sc_core::sc_time_stamp() << std::endl;
	return 0;
}
