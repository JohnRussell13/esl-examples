#include "sort_acc_ca_calculate.hpp"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

sort_acc_ca_calculate::sort_acc_ca_calculate(sc_module_name name) :
	sc_module(name)
{
	SC_CTHREAD(sort, clk.pos());
	reset_signal_is(rst,true);
}


void sort_acc_ca_calculate::sort()
{

	while(1)
	{
		cout << "Starting...\n";
		num = 0;
		out_tvalid.write(SC_LOGIC_0);
		out_tlast.write(SC_LOGIC_0);
		in_tready.write(SC_LOGIC_1);
		wait();

		while(1)
		{
			wait();
			//in_tready.write(SC_LOGIC_1);
			if (in_tvalid.read() == SC_LOGIC_1)
			{
                num = in_tdata.read();
				if(in_tlast.read() == SC_LOGIC_1)
				{
					break;
				}
			}
		}

		wait();
		cout << "Received transaction of value " << num << endl;
		in_tready.write(SC_LOGIC_0);

		nums[0] = 1;
		nums[1] = 1;

		for(num_t i=2; i != num; ++i)
		{
            wait();
            sc_int<16> v1 = nums[i-1];
            sc_int<16> v2 = nums[i-2];
            wait();
            sc_int<16> v3 = v1 + v2;
            wait();
            nums[i] = v3;
		}

		cout << "Cycle accurate core done sorting.\n";

		wait();
		num_t i = 0;
		sc_int<16> buf = nums[0];
		wait();
		sc_int<16> buf1 = nums[1];
		wait();

		while(i != num)
		{
			wait();
			out_tvalid.write(SC_LOGIC_1);
			out_tdata.write(buf);
			if (i == (num-1))
				out_tlast.write(SC_LOGIC_1);
			else
				out_tlast.write(SC_LOGIC_0);
			if (out_tready.read() == SC_LOGIC_1)
			{
				i++;
				buf = buf1;
				buf1 = nums[i+1];
			}
		}
		cout << "Transaction sent from cycle accurate core.\n";
		wait();
	}
}
