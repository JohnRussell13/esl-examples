#ifndef _SYS_HPP_
#define _SYS_HPP_

#include <systemc>
#include "module0.hpp"
#include "module1.hpp"

namespace comm
{
    using namespace sc_core;

    SC_MODULE(system)
    {
        public:
            SC_HAS_PROCESS(system);

            system(sc_module_name);

            sc_in<bool> gen;
            sc_out<bool> start;

            sc_export<sc_fifo<int>  > sort_o;
        protected:
            module0 m00;
            module0 m01;
            module0 m02;
            module1 m1;

            sc_signal<bool> med0;
            sc_signal<bool> med1;

            sc_signal<int> mix0;
            sc_signal<int> mix1;
            sc_signal<int> mix2;
    };


}
#endif
