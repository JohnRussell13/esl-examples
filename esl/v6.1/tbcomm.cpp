#include "tbcomm.hpp"

namespace comm
{
	using namespace sc_core;
	using namespace std;

	tbcomm::tbcomm(sc_module_name n) : sc_module(n), uut("UUT")
	{
		uut.gen(gen);
		uut.start(start);
		SC_THREAD(driver);
		SC_THREAD(monitor);
	}

	void tbcomm::driver()
	{
        wait(2, SC_NS);
        gen = true;
	}

	void tbcomm::monitor()
	{
        int d;
        while(1){
            if(uut.sort_o->num_available() != 0){
                while(uut.sort_o->nb_read(d)){
                    cout << d << " ";
                }
                cout << endl << "End" << endl;
            }
            wait(1, SC_NS);
        }
	}
}
