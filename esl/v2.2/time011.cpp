#include <systemc>
#include <iostream>

int sc_main(int argc, char* argv[])
{
    srand ( time (NULL) ) ;
    int x = rand() %10 +1;
    int y = rand() %10 +1;

	sc_start(x+y, sc_core::SC_NS);

	std::cout
		<< "First time = "
		<< x
		<< std::endl;

	std::cout
		<< "Second time = "
		<< y
		<< std::endl;

	std::cout
		<< "Current sim time = "
		<< sc_core::sc_time_stamp()
		<< std::endl;

    return 0;
}
