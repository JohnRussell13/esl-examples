#ifndef MODULE04_H
#define MODULE04_H

#include <systemc>
#include <deque>

SC_MODULE(Module04)
{
public:
	SC_HAS_PROCESS(Module04);

	Module04(sc_core::sc_module_name name);

	void life();

protected:
	int state;
};

#endif
