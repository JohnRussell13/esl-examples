#ifndef _MEM_MANAGER_HPP_
#define _MEM_MANAGER_HPP_

#include <tlm>
#include <deque>

class mem_manager :
	public tlm::tlm_mm_interface
{
	typedef tlm::tlm_base_protocol_types::tlm_payload_type pl_t;
public:

	pl_t* alloc();
	void free(pl_t*);
	~mem_manager();

protected:
	std::deque<pl_t*> pls;
};

#endif
