#include "module1.hpp"

namespace comm
{
	using namespace sc_core;
	using namespace std;

	module1::module1(sc_module_name n) : sc_module(n)
	{
		pexp.bind(fifo);//export
		cout << name() << " constructed.\n";
		SC_METHOD(process);
		sensitive << num0;
	}

	void module1::process()
	{
        f.push_back(num0);
        f.push_back(num1);
        f.push_back(num2);
        if(f.size() > 20){ //should be 100 but meh
            sort(f.begin(), f.end());
            for(vector<int>::iterator i = f.begin();  i != f.end(); i++){
                fifo.nb_write(*i);
            }
        }
	}

}
