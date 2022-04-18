#ifndef _SORT_IFS_HPP_
#define _SORT_IFS_HPP_

#include <systemc>
#include <vector>

class sort_write_if : virtual public sc_core::sc_interface
{
public:
	virtual void write(const int& data) = 0;
};

class sort_read_if : virtual public sc_core::sc_interface
{
public:
	virtual void read(std::vector<int>& data) = 0;
};

#endif
