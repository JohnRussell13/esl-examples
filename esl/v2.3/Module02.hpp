#ifndef MODULE02_H
#define MODULE02_H

#include <systemc>
#include <deque>

SC_MODULE(Module02)
{
public:
	SC_HAS_PROCESS(Module02);

	Module02(sc_core::sc_module_name name);

	void generate();
	void monitor();
protected:
	std::deque<long int> ints;
	int counter;
};

#endif
