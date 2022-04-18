#include "generator.hpp"

using namespace sc_core;
using namespace sc_dt;
using namespace tlm;

SC_HAS_PROCESS(generator);

generator::generator(sc_module_name name) :
	sc_module(name),
	isoc("isoc"),
	req_in_progess(false),
	m_peq(this, &generator::cb_peq)
{
	SC_THREAD(gen);
	isoc(*this);
}


void generator::gen()
{
	phase_t phase;
	sc_time delay = sc_time(4, SC_NS);
	tlm_sync_enum rsp;
	unsigned plnum = 0;

	int key_tb;

	for (unsigned int i = 0; i != 10; ++i)
	{
        key_tb = 1 + rand() % 13;
		unsigned int data_length = 1;
		unsigned int addr = 0;
		tlm_command cmd = TLM_WRITE_COMMAND;

		pl_t* pl = mm.alloc();
		unsigned char* data = pl->get_data_ptr();

		data[0] = key_tb;

		pl->set_command         ( cmd                     );
		pl->set_address         ( addr                    );
		pl->set_data_length     ( data_length             );
		pl->set_response_status ( TLM_INCOMPLETE_RESPONSE );
		pl->acquire();

		if(req_in_progess)
			wait(req_done);
		req_in_progess = true;

		plnum++;
		phase = BEGIN_REQ;
		std::string msg = "Send " + std::to_string(plnum) +
			" payload: " + std::to_string(key_tb);
		SC_REPORT_INFO("generator", msg.c_str());

		rsp = isoc->nb_transport_fw(*pl, phase, delay);

		assert(rsp == TLM_ACCEPTED && pl->get_response_status() == TLM_OK_RESPONSE);

        int fib_tb;
        int arr_tb[key_tb];

        arr_tb[0] = 1;
        arr_tb[1] = 1;

        for(int i = 2; i <= key_tb; i++){
            arr_tb[i] = arr_tb[i-1] + arr_tb[i-2];
        }

        fib_tb = arr_tb[key_tb-1];

		msg = "Testbench result -------- " + std::to_string(fib_tb);
		SC_REPORT_INFO("generator", msg.c_str());


		//5 hours later, still can't read into data...
		/*cmd = TLM_READ_COMMAND;
        addr = 0;
        data_length = 1;

        pl = mm.alloc();
        data = pl->get_data_ptr();

		pl->set_command         ( cmd                     );
		pl->set_address         ( addr                    );
		pl->set_data_length     ( data_length             );
		pl->set_response_status ( TLM_INCOMPLETE_RESPONSE );
		pl->acquire();

		if(req_in_progess)
			wait(req_done);
		req_in_progess = true;

		//plnum++;
		phase = BEGIN_REQ;
		msg = "Read data.";
		SC_REPORT_INFO("generator", msg.c_str());

		rsp = isoc->nb_transport_fw(*pl, phase, delay);

		assert(rsp == TLM_ACCEPTED && pl->get_response_status() == TLM_OK_RESPONSE);*/

		/*std::cout << (int)data[0] << std::endl;

		if(data[0] != (unsigned char) fib_tb){
            msg = "Test failed!";
		}
		else{
            msg = "Test passed.";
		}

		SC_REPORT_INFO("generator", msg.c_str());*/
	}
}

tlm_sync_enum generator::nb_transport_bw(pl_t& pl, phase_t& phase, sc_time& delay)
{
	assert(phase == END_REQ || phase == BEGIN_RESP);
	m_peq.notify(pl, phase);

	return TLM_ACCEPTED;
}

void generator::cb_peq(tlm_generic_payload& pl, const tlm_phase& phase)
{
	switch(phase)
	{
	case END_REQ:
	{
		SC_REPORT_INFO("generator", "Request accepted.");
		req_in_progess = false;
		req_done.notify();
		return;
	}
	case BEGIN_RESP:
	{
		tlm_phase ret_phase = END_RESP;
		sc_time delay(1, SC_NS);
		isoc->nb_transport_fw(pl, ret_phase, delay);
		return;
	}
	default:
		SC_REPORT_FATAL("generator", "Bad phase");
	}
}

void generator::invalidate_direct_mem_ptr(uint64 start, uint64 end)
{

}
