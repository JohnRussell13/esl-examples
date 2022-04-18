#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

#include <systemc>
#include <tlm>
#include <tlm_utils/peq_with_cb_and_phase.h>

class memory :
	public sc_core::sc_module,
	public tlm::tlm_fw_transport_if<>
{
public:
	memory(sc_core::sc_module_name);

	tlm::tlm_target_socket<> tsoc;

	typedef tlm::tlm_base_protocol_types::tlm_payload_type pl_t;
	typedef tlm::tlm_base_protocol_types::tlm_phase_type phase_t;

	void b_transport(pl_t&, sc_core::sc_time&);
	tlm::tlm_sync_enum nb_transport_fw(pl_t&, phase_t&, sc_core::sc_time&);
	bool get_direct_mem_ptr(pl_t&, tlm::tlm_dmi&);
	unsigned int transport_dbg(pl_t&);

protected:
    void calc();
	int key;
	int fib;

	//static const int RAM_SIZE = 1024;
	//unsigned char ram[RAM_SIZE];
	tlm_utils::peq_with_cb_and_phase<memory> m_peq;

	bool resp_in_progess;
	sc_core::sc_event resp_done;

	void cb_peq(tlm::tlm_generic_payload&, const tlm::tlm_phase&);
};

#endif
