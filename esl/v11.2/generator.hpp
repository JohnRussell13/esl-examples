#ifndef _GENERATOR_HPP_
#define _GENERATOR_HPP_

#include <systemc>
#include <tlm>
#include "mem_manager.hpp"
#include <tlm_utils/peq_with_cb_and_phase.h>

class generator :
	public sc_core::sc_module,
	public tlm::tlm_bw_transport_if<>
{
public:
	generator(sc_core::sc_module_name);

	tlm::tlm_initiator_socket<> isoc;

	typedef tlm::tlm_base_protocol_types::tlm_payload_type pl_t;
	typedef tlm::tlm_base_protocol_types::tlm_phase_type phase_t;

	tlm::tlm_sync_enum nb_transport_bw(pl_t&, phase_t&, sc_core::sc_time&);
	void invalidate_direct_mem_ptr(sc_dt::uint64, sc_dt::uint64);

protected:
	void gen();
	bool req_in_progess;
	sc_core::sc_event req_done;
	tlm_utils::peq_with_cb_and_phase<generator> m_peq;
	mem_manager mm;

	void cb_peq(tlm::tlm_generic_payload&, const tlm::tlm_phase&);
};

#endif
