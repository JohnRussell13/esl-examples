#define SC_INCLUDE_FX
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
		arsize = 0;
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
				x_ca[arsize++] = in_tdata;
				if(in_tlast.read() == SC_LOGIC_1)
				{
					break;
				}
			}
		}
		/*for(int i = 0; i < arsize; i++){
            cout << x_ca[i] << " ";
		}
		cout << endl;*/

		wait();
		cout << "Received transaction of size " << arsize << endl;
		in_tready.write(SC_LOGIC_0);

        sc_fixed<16,5> x0, x1, x2, x3, y1, y2, y3, y4, y5, temp;
        sc_fixed<16,5> sum;

        for (int i=0; i != 5; ++i){
            y_ca[i] = 0;
            wait();
        }

        for (int i=5; i != arsize; ++i)
        {//0.5 0.1 -0.2 0 1 | 0.8 0.4 0.7 -1.2
            wait();
            temp = x_ca[i];
            wait();
            x0 = 0.8*temp;
            wait();
            temp = x_ca[i-1];
            wait();
            x1 = 0.4*temp;
            wait();
            temp = x_ca[i-2];
            wait();
            x2 = 0.7*temp;
            wait();
            temp = x_ca[i-3];
            wait();
            x3 = -1.2*temp;

            wait();
            temp = y_ca[i-1];
            wait();
            y1 = -0.5*temp;
            wait();
            temp = y_ca[i-2];
            wait();
            y2 = -0.1*temp;
            wait();
            temp = y_ca[i-3];
            wait();
            y3 = 0.2*temp;
            wait();
            temp = y_ca[i-4];
            wait();
            y4 = 0*temp;
            wait();
            temp = y_ca[i-5];
            wait();
            y5 = -1*temp;

            wait();
            sum = x0+x1;
            //cout << sum << " VS " << 0.8*x_ca[i] + 0.4*x_ca[i-1] << endl;
            wait();
            sum = sum + x2;
            wait();
            sum = sum + x3;
            wait();
            sum = sum + y1;
            wait();
            sum = sum + y2;
            wait();
            sum = sum + y3;
            wait();
            sum = sum + y4;
            wait();
            sum = sum + y5;
            wait();
            y_ca[i] = sum;

            //code above will be different because code below uses higher precison
            //uncomment previous comment for example
            //y_ca[i] = -0.5*y_ca[i-1] - 0.1*y_ca[i-2] + 0.2*y_ca[i-3] - 0*y_ca[i-4] - 1*y_ca[i-5] + 0.8*x_ca[i] + 0.4*x_ca[i-1] + 0.7*x_ca[i-2] - 1.2*x_ca[i-3];
        }

	  /*for (int i = 0; i != arsize; ++i)
		{
		  cout << y_ca[i] << " ";
		}*/

		cout << "Cycle accurate core done sorting.\n";

		int i = 0;
		sc_fixed<16,5> buf = y_ca[0];
		wait();
		sc_fixed<16,5> buf1 = y_ca[1];
		wait();

		while(i != arsize)
		{
			wait();
			out_tvalid.write(SC_LOGIC_1);
			out_tdata.write(buf);
			if (i == (arsize-1))
				out_tlast.write(SC_LOGIC_1);
			else
				out_tlast.write(SC_LOGIC_0);
			if (out_tready.read() == SC_LOGIC_1)
			{
				i++;
				buf = buf1;
				buf1 = y_ca[i+1];
			}
		}
		cout << "Transaction sent from cycle accurate core.\n";
		wait();
	}
}
