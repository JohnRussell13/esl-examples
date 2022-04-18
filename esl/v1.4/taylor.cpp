#define SC_INCLUDE_FX
#include <systemc>
#include <iostream>
#include <cmath>

int sc_main(int argc, char* argv[])
{
    double x;
    double fact = 1, powx;
    double sin_ap = 0;
    double sin_ex = 0;
    double err = 1e-5;
    do{
        std::cin >> x;
    }
    while(x > 6.28); //so that we can have fixed F
    powx = x;
    sin_ex = sin(x);
    int n = 0;

	std::cout << "Exact value: " << sin_ex << std::endl;
	// Main loop for model 1
	do
	{
        sin_ap += -((double)(n%2)*2-1)/fact * powx;
        std::cout << "Approximate value for n = " << n << ": "<< sin_ap << std::endl;
        n++;
        powx *= x*x;
        fact *= 2*n*(2*n+1);
	} while(std::abs(sin_ap - sin_ex) > err);

	std::cout << std::endl;
	int W = 5;
	int F = 2;
	bool check;

	//model 2
	int i;
	sin_ex = sin_ap;
	do
	{
        /*sc_dt::sc_fix_fast x_f(W,F);
        sc_dt::sc_fix_fast fact_f(W,F), powx_f(W,F);*/
        sc_dt::sc_fix_fast sin_f(W,F);
        /*x_f = x;*/
        fact = 1;
        powx = x;

        sin_ap = 0;
        sin_f = 0;
        i = 0;
        while(i < n){
            //sin_f += -((i%2)*2-1)/fact_f * powx_f;
            //powx_f *= x_f*x_f;
            //fact_f *= 2*i*(2*i+1);
            sin_ap += -((i%2)*2-1)/fact * powx;
            i++;
            powx *= x*x;
            fact *= 2*i*(2*i+1);
            sin_f = sin_ap;
        }

        std::cout << "Approximate value for format 2." << W-F << ": "<< sin_f << std::endl;
        W++;
        check = (std::abs(sin_f - sin_ex) > err);
	} while(check);

	return 0;
}
