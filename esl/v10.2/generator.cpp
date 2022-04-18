#include "generator.hpp"

using namespace sc_core;
using namespace sc_dt;
using namespace tlm;

SC_HAS_PROCESS(generator);

generator::generator(sc_module_name name) :
	sc_module(name),
	isoc("isoc")
{
	SC_THREAD(gen);
	isoc(*this);
}

void generator::gen()
{
	tlm_generic_payload pl;
	sc_time offset = SC_ZERO_TIME;
	unsigned char buf[0];

	// Normal TLM transport interface.
	for (unsigned int i = 0; i != 10; ++i)
	{
        int key_tb = 1 + rand() % 14;
        int arr_tb[key_tb];
		unsigned int data_length = 1;
		unsigned int addr = 0;
		tlm_command cmd = TLM_WRITE_COMMAND;
		std::string msg = "Write Fib num ";
		msg += std::to_string(key_tb);

		buf[0] = (unsigned char) key_tb;

		pl.set_command         ( cmd                     );
		pl.set_address         ( addr                    );
		pl.set_data_ptr        ( buf                     );
		pl.set_data_length     ( data_length             );
		pl.set_response_status ( TLM_INCOMPLETE_RESPONSE );

		offset += sc_time(4, SC_NS);

		isoc->b_transport(pl, offset);
		SC_REPORT_INFO("generator", msg.c_str());

        int fib_tb;

        arr_tb[0] = 1;
        arr_tb[1] = 1;

        for(int i = 2; i != key_tb; i++){
            arr_tb[i] = arr_tb[i-1] + arr_tb[i-2];
        }

        fib_tb = arr_tb[key_tb-1];

		cmd = TLM_READ_COMMAND;
		msg = "Read Fib num";

		pl.set_command         ( cmd                     );
		pl.set_address         ( addr                    );
		pl.set_data_ptr        ( buf                     );
		pl.set_data_length     ( data_length             );
		pl.set_response_status ( TLM_INCOMPLETE_RESPONSE );

		offset += sc_time(4, SC_NS);

		isoc->b_transport(pl, offset);
		SC_REPORT_INFO("generator", msg.c_str());

		if(buf[0] != (unsigned char) fib_tb){
            msg = "Test failed!";
		}
		else{
            msg = "Test passed.";
		}

		SC_REPORT_INFO("generator", msg.c_str());
	}
}

tlm_sync_enum generator::nb_transport_bw(pl_t& pl, phase_t& phase, sc_time& offset)
{
	return TLM_ACCEPTED;
}

void generator::invalidate_direct_mem_ptr(uint64 start, uint64 end)
{

}
