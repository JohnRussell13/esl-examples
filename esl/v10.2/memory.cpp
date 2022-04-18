#include "memory.hpp"

using namespace sc_core;
using namespace tlm;
using namespace sc_dt;

SC_HAS_PROCESS(memory);

memory::memory(sc_module_name name) :
	sc_module(name),
	tsoc("tsoc"),
	key(0),
	fib(0)
{
	SC_THREAD(calc);
	tsoc(*this);
}

void memory::calc(){
    int arr[key];
    arr[0] = 1;
    arr[1] = 1;
    for(int i = 2; i < key; i++){
        arr[i] = arr[i-1] + arr[i-2];
    }
    fib = arr[key-1];
    key = 0;
}

void memory::b_transport(pl_t& pl, sc_time& offset)
{
	tlm_command cmd    = pl.get_command();
	//uint64 adr         = pl.get_address();
	unsigned char *buf = pl.get_data_ptr();
	unsigned int len   = pl.get_data_length();

	switch(cmd)
	{
	case TLM_WRITE_COMMAND:
		for (unsigned int i = 0; i != len; ++i)
			key = (int) buf[i];
		pl.set_response_status( TLM_OK_RESPONSE );
		calc();
		break;
	case TLM_READ_COMMAND:
		for (unsigned int i = 0; i != len; ++i)
			buf[i] = (unsigned char) fib;
		pl.set_response_status( TLM_OK_RESPONSE );
		break;
	default:
		pl.set_response_status( TLM_COMMAND_ERROR_RESPONSE );
	}

	offset += sc_time(3, SC_NS);
}

tlm_sync_enum memory::nb_transport_fw(pl_t& pl, phase_t& phase, sc_time& offset)
{
	return TLM_ACCEPTED;
}

bool memory::get_direct_mem_ptr(pl_t& pl, tlm_dmi& dmi)
{

}

unsigned int memory::transport_dbg(pl_t& pl)
{

}
