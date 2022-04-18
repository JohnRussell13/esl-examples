#define SC_INCLUDE_FX
#include <systemc>
#include <iostream>
#include <deque>
#include <vector>
#include <cmath>

typedef sc_dt::sc_ufix_fast num_t;
typedef std::deque<num_t> array_t;
typedef std::vector<long int> orig_array_t;

bool passCheck(const orig_array_t& gold, const array_t& sys,
			   double delta)
{
	for (size_t i = 0; i != sys.size(); ++i)
	{
		if (std::abs(gold[i] - sys[i]) > delta)
			return false;
	}
	return true;
}

int sc_main(int argc, char* argv[])
{
	orig_array_t gold;
	gold.clear();
	gold.push_back(0);
	gold.push_back(1);

    for(int i; i < 64; i++){
        gold.push_back(gold[i] + gold[i+1]);
    }

	const double error_d = 0.5;
	int W = 1;

	bool pass = false;

	size_t n;
	std::cin >> n;

	// Main loop
	do
	{
		std::cout <<
			"Starting pass for number format " << W <<
			"." << 0 << std::endl;

		// Convert numbers
        num_t d(W, W);
        array_t sys(W,W);
		sys.clear();
        sys.push_back(0);
        sys.push_back(1);

		// Calculate output
		std::cout << sys[0] << std::endl;
		std::cout << sys[1] << std::endl;
		for (size_t i = 0; i < n-2; ++i)
		{
            d = sys[i]+sys[i+1];
            sys.push_back(d);
            std::cout << sys[i+2] << std::endl;
		}

		// Check if error is small enough
		pass = passCheck(gold, sys, error_d);
		sys.clear();
		W++;
	} while(pass == false);

	std::cout << std::endl;

	return 0;
}
