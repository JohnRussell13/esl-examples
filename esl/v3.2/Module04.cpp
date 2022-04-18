#include "Module04.hpp"
#include <cstdlib>
#include <ctime>

using namespace sc_core;
using namespace std;

Module04::Module04(sc_core::sc_module_name name)
{
	SC_THREAD(life);
	srand(time(NULL));
}

void Module04::life()
{
    static sc_core::sc_event s1;
	static int total = 0;
	static int fl = 0;
	state = 0;

	while(true){
        if(fl == 0){
            state = 1;
            fl = 1;
        }
        if(state == 0){
            if(rand() % 100 < 99){//around 95 is edge case
                wait(s1);
            }
            else{
                state = 1;
            }
        }
        if(state == 1){
            wait(rand()%10 + 1, sc_core::SC_NS);
            total++;
            state = 2;
            std::cout << total << endl;
            s1.notify();
        }
        if(state == 2){
            wait(s1);
        }
	}
}
