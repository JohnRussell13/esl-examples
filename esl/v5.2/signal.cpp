#include <systemc>
#include <iostream>

using namespace sc_core;
using namespace std;

SC_MODULE(TwoFlops)
{
public:
	SC_HAS_PROCESS(TwoFlops);

	TwoFlops(sc_module_name);

protected:

	sc_signal<double> a[2];
	sc_signal<double> b[3];
	sc_signal<double> x[3];
	sc_signal<double> y[2];
	sc_signal<bool> clk;
	sc_signal<double> sys;

	bool fl;

	void clk_gen();
	void comb();
	void seq();
};

TwoFlops::TwoFlops(sc_module_name name) : sc_module(name)
{
	SC_THREAD(comb);
	SC_METHOD(seq);
	sensitive << clk.posedge_event();
	SC_THREAD(clk_gen);
	a[0] = 0.5;
	a[1] = 0.2;
	b[0] = 1.2;
	b[1] = 0.3;
	b[2] = 0.2;
	x[0] = 1;
	x[1] = 0;
	x[2] = 0;
	y[0] = 0;
	y[1] = 0;
	sys = 0;
	fl = false;
}

void TwoFlops::clk_gen()
{
    wait(5, SC_NS);

	while(1)
	{
		clk = true;
		wait(10, SC_NS);
		clk = false;
		wait(10, SC_NS);
	}
}

void TwoFlops::comb()
{

    while(1){
        wait(1, SC_NS);
        sys = -a[0]*y[0] - a[1]*y[1] + b[0]*x[0] + b[1]*x[1] + b[2]*x[2];//can't be a loop, not without wait (signal!)
        /*
        sys = 0;
        wait();
        for(int i = 0; i < 2; i++){
            sys = sys - a[i]*y[i];
            wait(1, SC_FS);
        }
        for(int i = 0; i < 3; i++){
            sys = sys + b[i]*x[i];
            sys = 5;
            wait(1, SC_FS);
        }*/
        wait(clk.posedge_event());
    }
}

void TwoFlops::seq()
{
    if(fl){
        x[2] = x[1];
        x[1] = x[0];
        x[0] = 0;
        y[1] = y[0];
        y[0] = sys;
    }
    else fl = true;

	cout << sys << endl;
}

int sc_main(int argc, char* argv[])
{
	TwoFlops uut("UUT");

	sc_start(200, SC_NS);

    return 0;
}
