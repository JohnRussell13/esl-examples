#include "module0.hpp"
#include <ctime>

namespace comm
{
	using namespace sc_core;
	using namespace std;

	module0::module0(sc_module_name n) : sc_module(n)
	{
		cout << name() << " constructed.\n";
		SC_THREAD(process);
        srand(time(NULL));
	}

	void module0::process()
	{
        while(1){
            if(gen){
                wait(rand()%6 + 5, SC_NS);
                g = rand()%100;
                //cout << name() << " rand: " << g << endl;
                num->write(g);
                start->write(true);
            }
            else{
                wait(1, SC_NS);
            }
        }
	}
}
