#include "sort_acc_tlm.hpp"

using namespace std;
using namespace sc_core;

sort_acc_tlm::sort_acc_tlm(sc_module_name name) : sc_channel(name)
{
	cout << "Constructed.\n";
}

void sort_acc_tlm::write(const int& data)
{
    num = data;
	cout << "Datum " << data << " writen to accelerator.\n";
	calculate();
}

void sort_acc_tlm::calculate()
{
    int sum;
    fibs.clear();
    fibs.push_back(1);
    fibs.push_back(1);
	  for(int i = 2; i < num; i++){
            sum = fibs[i-1] + fibs[i-2];
            fibs.push_back(sum);
	  }
}

void sort_acc_tlm::read(std::vector<int>& data)
{
	data.clear();
	for (size_t i = 0; i != fibs.size(); ++i)
		data.push_back(fibs[i]);
	cout << "Data of size " << data.size() << " read from accelerator.\n";
}
