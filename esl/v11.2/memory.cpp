#include "memory.hpp"

using namespace sc_core;
using namespace tlm;
using namespace sc_dt;

memory::memory(sc_module_name name) :
	sc_module(name),
	tsoc("tsoc"),
	m_peq(this, &memory::cb_peq),
	resp_in_progess(false),
	key(0),
	fib(0)
{
	tsoc(*this);
	/*for (int i = 0; i != RAM_SIZE; ++i)
		ram[i] = 0;*/
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
    //std::cout << fib << std::endl;
}

void memory::b_transport(pl_t& pl, sc_time& delay)
{

}

tlm_sync_enum memory::nb_transport_fw(pl_t& pl, phase_t& phase, sc_time& delay)
{
	m_peq.notify(pl, phase, delay);
	pl.set_response_status(TLM_OK_RESPONSE);
	return TLM_ACCEPTED;
}

void memory::cb_peq(tlm_generic_payload& pl, const tlm_phase& phase)
{
	switch(phase)
	{
	case BEGIN_REQ:
	{

		tlm_command cmd    = pl.get_command();
		uint64 adr         = pl.get_address();
		unsigned char *buf = pl.get_data_ptr();
		unsigned int len   = pl.get_data_length();
		std::string msg;

		switch(cmd)
		{
		case TLM_WRITE_COMMAND:
			for (unsigned int i = 0; i != len; ++i)
				key = (int) buf[i];
			msg = "Write";
			calc();
			break;
		case TLM_READ_COMMAND:
			for (unsigned int i = 0; i != len; ++i)
				buf[i] = (unsigned char) fib;
            //std::cout << (int) buf[0] << std::endl;
			msg = "Read";
			break;
		default:
			pl.set_response_status( TLM_COMMAND_ERROR_RESPONSE );
		}

		msg += " at time " + sc_time_stamp().to_string() + " value -------- " + std::to_string(fib);

		SC_REPORT_INFO("memory status", msg.c_str());

		sc_time delay(5, SC_NS);
		tlm_phase ret_phase = END_REQ;
		tlm_sync_enum rsp = tsoc->nb_transport_bw(pl, ret_phase, delay);

		assert(rsp == TLM_ACCEPTED);
		sc_time fw_delay(10, SC_NS);
		tlm_phase fw_phase = BEGIN_RESP;
		m_peq.notify(pl, fw_phase, fw_delay);

		break;

	}

	case BEGIN_RESP:
	{
		if(resp_in_progess)
			wait(resp_done);
		resp_in_progess = true;
		sc_time delay(3, SC_NS);
		tlm_phase fw_phase = BEGIN_RESP;
		tsoc->nb_transport_bw(pl, fw_phase, delay);
		break;
	}

	case END_RESP:
	{
		resp_in_progess = false;
		resp_done.notify();
		SC_REPORT_INFO("memory", "Transaction finished.");
		pl.release();
		break;
	}

	default:
		SC_REPORT_FATAL("memory", "Bad phase");
	}
}

bool memory::get_direct_mem_ptr(pl_t& pl, tlm_dmi& dmi)
{
	return false;
}

unsigned int memory::transport_dbg(pl_t& pl)
{
	return 0;
}
