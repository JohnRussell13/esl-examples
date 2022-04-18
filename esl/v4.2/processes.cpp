#include <systemc>
#include <iostream>

using namespace sc_core;

SC_MODULE(Proc)
{
public:
	SC_HAS_PROCESS(Proc);

	Proc(sc_module_name);

protected:
	void print(const char *str);

	sc_event a, b, c;
	void a_thread();
	void b_thread();
	void c_thread();
	void dynamic_method();
	int door_a, door_b, door_c;
	int state;
    sc_time d;
};

Proc::Proc(sc_module_name name) : sc_module(name)
{
	SC_THREAD(a_thread);
	SC_THREAD(b_thread);
	SC_THREAD(c_thread);
	SC_METHOD(dynamic_method);
	sensitive << a << b << c;
	door_a = 0;
	door_b = 0;
	door_c = 0;
	state = 0;
}

void Proc::a_thread()
{
	while(1)
	{
		wait(rand()%5 + 3, SC_SEC);
        door_a = ~door_a;
		a.notify();
	}
}

void Proc::b_thread()
{
	while(1)
	{
		wait(rand()%5 + 3, SC_SEC);
        door_b = ~door_b;
		b.notify();
	}
}

void Proc::c_thread()
{
	while(1)
	{
		wait(rand()%5 + 3, SC_SEC);
        door_c = ~door_c;
		c.notify();
	}
}

void Proc::dynamic_method()
{
    sc_time lim(5, SC_SEC);
    if(sc_time_stamp() - d > lim) state = 0;
    if(state == 0){
        next_trigger(a);
        if(door_a) state++;
    }
    else if(state == 1){
        next_trigger(b);
        if(door_b) state++;
    }
    else if(state == 2){
        next_trigger(c);
        if(door_a) state++;
    }
    if(state == 3){
        std::cout << "@" << sc_time_stamp() << std::endl;
        state = 0;
        door_a = 0;
        door_b = 0;
        door_c = 0;
    }
    d = sc_time_stamp();
}

int sc_main(int argc, char* argv[])
{
	Proc uut("UUT");

	sc_start(100, SC_SEC);

    return 0;
}
