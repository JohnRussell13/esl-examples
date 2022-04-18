#define SC_INCLUDE_FX
#include "sort_gen_check.hpp"
#include <algorithm>

using namespace std;
using namespace sc_core;

sort_gen_check::sort_gen_check(sc_module_name name) :
	sc_module(name)
{
  cout << "Constructed\n";
  SC_THREAD(test);
}

void sort_gen_check::test()
{
  for(int testnum = 0; testnum != 10; testnum++)//fixed 10 tests
	{
	  //	Generate lengths from 10 to 20
	  int len = 10 + rand() % 11;
	  vector<sc_dt::sc_fixed<16,5> > x;

	  cout << "Generate transaction of " << len << " integers.\n";

	  for (int i=0; i != len; ++i)
		{
		  sc_dt::sc_fixed<16,5> num = rand() % 11 - 5; //$x \in [-5,5]$
		  x.push_back(num);
		}

	  wr_port->write(x);
	  cout << "Transaction sent.\n";

	  vector<sc_dt::sc_fixed<16,5> > y;
	  y.clear();
	  for (int i=0; i != 5; ++i)
		{
		  y.push_back(0.0);
		}

      sc_dt::sc_fixed<16,5> sum;

	  for (int i=5; i != len; ++i)
		{//0.5 0.1 -0.2 0 1 | 0.8 0.4 0.7 -1.2
		  sum = -0.5*y[i-1] - 0.1*y[i-2] + 0.2*y[i-3] - 0*y[i-4] - 1*y[i-5] + 0.8*x[i] + 0.4*x[i-1] + 0.7*x[i-2] - 1.2*x[i-3];
		  y.push_back(sum);
		}


	  vector<sc_dt::sc_fixed<16,5> > res;
	  rd_port->read(res);
	  cout << "Transaction received.\n";

	  if(y.size() != res.size())
		{
		  cout << "Test failed.\n";
		  cout << "Expected size " << y.size() << endl;
		  cout << "Received size " << res.size() << endl;
		  return;
		}
        double prec = 10;
	  for (size_t i = 0; i != y.size(); ++i)
		{
		  //cout << round(y[i] * prec)/prec << " VS " << round(res[i] * prec)/prec << endl;
		  if(round(y[i] * prec)/prec != round(res[i] * prec)/prec)
			{
			  cout << "Test " << testnum << " failed.\n";
			  cout << "Elemnt with index " << i << endl;
			  cout << "Expected value " << y[i] << endl;
			  cout << "Received value " << res[i] << endl;
			  return;
			}
		}

	  cout << "Test " << testnum << " passed.\n";

	  /*for (size_t i = 0; i != y.size(); ++i)
		{
		  cout << y[i] << " ";
		}
      cout << endl;*/

	  /*for (size_t i = 0; i != res.size(); ++i)
		{
		  cout << res[i] << " ";
		}*/
      cout << endl;
	}
}
