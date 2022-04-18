#define SC_INCLUDE_FX
#include "sort_acc_tlm.hpp"

using namespace std;
using namespace sc_core;

sort_acc_tlm::sort_acc_tlm(sc_module_name name) : sc_channel(name)
{
	cout << "Constructed.\n";
}

void sort_acc_tlm::write(const std::vector<sc_dt::sc_fixed<16,5> >& data)
{
	x_tlm.clear();
	for (size_t i = 0; i != data.size(); ++i)
		x_tlm.push_back(data[i]);
	cout << "Date of size " << data.size() << " writen to accelerator.\n";

	calculate();
}

void sort_acc_tlm::calculate()
{
    y_tlm.clear();

    for (int i=0; i != 5; ++i)
    {
        y_tlm.push_back(0);
    }

    sc_dt::sc_fixed<16,5> sum;

    for (size_t i=5; i != x_tlm.size(); ++i)
	{//0.5 0.1 -0.2 0 1 | 0.8 0.4 0.7 -1.2
        sum = -0.5*y_tlm[i-1] - 0.1*y_tlm[i-2] + 0.2*y_tlm[i-3] - 0*y_tlm[i-4] - 1*y_tlm[i-5] + 0.8*x_tlm[i] + 0.4*x_tlm[i-1] + 0.7*x_tlm[i-2] - 1.2*x_tlm[i-3];
        y_tlm.push_back(sum);
	}
}

void sort_acc_tlm::read(std::vector<sc_dt::sc_fixed<16,5> >& data)
{
	data.clear();
	for (size_t i = 0; i != y_tlm.size(); ++i)
		data.push_back(y_tlm[i]);
	cout << "Date of size " << data.size() << " read from accelerator.\n";
}
