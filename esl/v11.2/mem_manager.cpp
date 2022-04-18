#include "mem_manager.hpp"

using namespace std;
using namespace tlm;

mem_manager::pl_t* mem_manager::alloc()
{
	pl_t* p_pl;

	if(pls.empty())
	{
		p_pl = new pl_t(this);
		unsigned char* data = new unsigned char [100];
		p_pl->set_data_ptr(data);
	}
	else
	{
		p_pl = pls.front();
		pls.pop_front();
		SC_REPORT_INFO("Manager", "reuse!");
	}

	return p_pl;
}

void mem_manager::free(pl_t* p_pl)
{
	p_pl->reset();
	pls.push_back(p_pl);
}

mem_manager::~mem_manager()
{
	for (size_t i = 0; i != pls.size(); ++i)
	{
		delete [] pls[i]->get_data_ptr();
		delete pls[i];
	}
	pls.clear();
}
