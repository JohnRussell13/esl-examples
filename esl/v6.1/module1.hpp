#ifndef _MODULE1_HPP_
#define _MODULE1_HPP_

#include <systemc>

namespace comm
{
	using namespace sc_core;

	SC_MODULE(module1)
	{
        public:
            SC_HAS_PROCESS(module1);

            module1(sc_core::sc_module_name);

            sc_in<int> num0;
            sc_in<int> num1;
            sc_in<int> num2;

            sc_export<sc_fifo<int> > pexp;

        protected:
            void process();
            sc_fifo<int> fifo;
            std::vector<int> f;
	};

}
#endif
