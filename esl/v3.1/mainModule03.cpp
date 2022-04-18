#include <systemc>
#include "Module03.hpp"

int sc_main(int argc, char* argv[])
{
	Module03 uut("UUT");

	sc_start(1, sc_core::SC_US);

	std::cout << "Simulation finished at " << sc_core::sc_time_stamp() << std::endl;
	return 0;
}
