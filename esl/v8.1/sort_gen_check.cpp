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
  for(int testnum = 0; testnum != 10; testnum++)
	{
	  //	Generate lengths from 10 to 100
	  int len = 1 + rand() % 30;

	  cout << "Generate Fib num of position " << len << ".\n";

	  wr_port->write(len);
	  cout << "Transaction sent.\n";

	  vector<int> tran;
	  tran.clear();
	  tran.push_back(1);
	  tran.push_back(1);
	  int sum;

	  for(int i = 2; i < len; i++){
            sum = tran[i-1] + tran[i-2];
            tran.push_back(sum);
	  }

        //read all Fib nums until len, minimal diff
	  vector<int> res;
	  rd_port->read(res);
	  cout << "Transaction received.\n";

	  if(tran.size() != res.size())
		{
		  cout << "Test failed.\n";
		  cout << "Expected size " << tran.size() << endl;
		  cout << "Received size " << res.size() << endl;
		  return;
		}

	  for (size_t i = 0; i != tran.size(); ++i)
		{
		  cout << tran[i] << " ";
		}
		cout << endl;

	  for (size_t i = 0; i != tran.size(); ++i)
		{
		  cout << res[i] << " ";
		}
		cout << endl;

	  for (size_t i = 0; i != tran.size(); ++i)
		{
		  if(tran[i] != res[i])
			{
			  cout << "Test " << testnum << " failed (overflow, intetnional).\n";
			  cout << "Elemnt with index " << i << endl;
			  cout << "Expected value " << tran[i] << endl;
			  cout << "Received value " << res[i] << endl;
			  return;
			}
		}

	  cout << "Test " << testnum << " passed.\n";
	}
}
