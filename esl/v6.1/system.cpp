#include "system.hpp"

namespace comm
{
	using namespace sc_core;
	using namespace std;

	system::system(sc_module_name n) :
		sc_module(n),
		m00("m00"),
		m01("m01"),
		m02("m02"),
		m1("m1")
	{
		cout << name() << " constructed.\n";
		m00.gen(gen);//link input
		m00.start(med0);//link output
		m00.num(mix0);//link output

		m01.gen(med0);//link input
		m01.start(med1);//link output
		m01.num(mix1);//link output

		m02.gen(med1);//link input
		m02.start(start);//link output
		m02.num(mix2);//link output

		sort_o(m1.pexp);//link export
		m1.num0(mix0);
		m1.num1(mix1);
		m1.num2(mix2);
	}
}

