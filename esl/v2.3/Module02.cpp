#include "Module02.hpp"
#include <cstdlib>
#include <ctime>

using namespace sc_core;
using namespace std;

Module02::Module02(sc_core::sc_module_name name)
{
	SC_THREAD(generate);
 	SC_THREAD(monitor);
	srand(time(NULL));
}

void Module02::generate()
{
	while(true){
        ints.clear();
        wait(rand()%91 + 10, SC_NS);
        counter++;
        ints.push_back(0);
        wait(rand()%91 + 10, SC_NS);
        counter++;
        ints.push_back(1);
        while(ints.size() < 64)
        {
            wait(rand()%91 + 10, SC_NS);
            long int val = ints[ints.size()-1] + ints[ints.size()-2];
            counter++;
            ints.push_back(val);
        }
	}
}

void Module02::monitor()
{
	for(;;)
	{
		counter = 0;
		wait(1, SC_SEC);
		std::cout << "Number " << counter <<
				" at time " << sc_time_stamp() <<
				".\n";
	}
}
