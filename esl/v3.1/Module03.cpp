#include "Module03.hpp"
#include <cstdlib>
#include <ctime>

using namespace sc_core;
using namespace std;

Module03::Module03(sc_core::sc_module_name name)
{
	SC_THREAD(generate);
 	SC_THREAD(monitor);
	srand(time(NULL));
}

void Module03::generate()
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
            s1.notify(5, SC_NS);
            ints.push_back(val);
        }
	}
}

void Module03::monitor()
{
	for(;;)
	{
		counter = 0;
		wait(s1);
		std::cout << "Number " << counter <<
				" at time " << sc_time_stamp() <<
				".\n";
	}
}
