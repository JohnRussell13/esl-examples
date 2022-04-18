#include <systemc>
#include <iostream>

int sc_main(int argc, char* argv[])
{
    srand ( time (NULL) ) ;
    int x = rand() %90 +10;

	sc_start(x, sc_core::SC_NS);

	std::cout
		<< "Current sim time = "
		<< sc_core::sc_time_stamp()
		<< std::endl;

    return 0;
}
