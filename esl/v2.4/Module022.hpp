#ifndef MODULE022_H
#define MODULE022_H

#include <systemc>
#include <deque>

SC_MODULE(Module022)
{
public:
	SC_HAS_PROCESS(Module022);

	Module022(sc_core::sc_module_name name);

	void loto();
	void p1();
	void p2();
	void p3();
	void judge();
protected:
	std::deque<int> numbers;
	std::deque<int> p1_n;
	std::deque<int> p2_n;
	std::deque<int> p3_n;
	bool p1_b, p2_b, p3_b;
};

#endif
