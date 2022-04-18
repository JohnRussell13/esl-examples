#include <systemc>
#include <iostream>

using namespace sc_core;

SC_MODULE(BusGen)
{
public:
	SC_HAS_PROCESS(BusGen);

	BusGen(sc_module_name name, sc_mutex*, sc_mutex*);

protected:
	sc_mutex* m1;
	sc_mutex* m2;

	void proc();
};

BusGen::BusGen(sc_module_name name, sc_mutex* m1, sc_mutex* m2) : sc_module(name), m1(m1), m2(m2)
{
	SC_THREAD(proc);
	srand(time(NULL));
}

void BusGen::proc()
{
		wait(rand()%10+1, SC_NS);
		m1->lock();
		m2->lock();
		std::cout << "@ " << sc_time_stamp() <<
			" taken by " << name() << std::endl;
		wait(300, SC_NS);
		m1->unlock();
		m2->unlock();
}

int sc_main(int argc, char* argv[])
{
	sc_mutex mtx1;
	sc_mutex mtx2;
	sc_mutex mtx3;
	sc_mutex mtx4;
	sc_mutex mtx5;
	BusGen f1("f1", &mtx1, &mtx2);
	BusGen f2("f2", &mtx2, &mtx3);
	BusGen f3("f3", &mtx3, &mtx4);
	BusGen f4("f4", &mtx4, &mtx5);
	BusGen f5("f5", &mtx5, &mtx1);

	sc_start(5000, SC_NS);

    return 0;
}
