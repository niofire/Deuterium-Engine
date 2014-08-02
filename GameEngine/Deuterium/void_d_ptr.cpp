#include "void_d_ptr.h"

namespace deuterium
{

	
void_d_ptr::void_d_ptr()
{
	_num_handles_allocated = NULL;
	_ptr = NULL;

}


void_d_ptr::void_d_ptr(void* ptr)
{
	_num_handles_allocated = NULL;
	_ptr = NULL;

	alloc(ptr);
}

void_d_ptr::void_d_ptr(const void_d_ptr& ptr)
{
	this->_ptr = NULL;
	this->_num_handles_allocated = NULL;

	//update the num of allocated handles
	this->_num_handles_allocated = ptr._num_handles_allocated;
	this->add_handle();
	
	this->_ptr = ptr._ptr;
}


void_d_ptr::~void_d_ptr()
{
	this->clear();
}


void void_d_ptr::alloc(void* ptr)
{
	//clear previous reference
	this->clear();

	//store the newly allocated pointer
	_num_handles_allocated = new int(1);
	_ptr = ptr;
}

void void_d_ptr::clear()
{
	if(this->_num_handles_allocated != NULL)
	{
		*_num_handles_allocated = *_num_handles_allocated - 1;
		this->delete_unused_memory();
	}

	this->_ptr = NULL;
	this->_num_handles_allocated = NULL;
}


void void_d_ptr::add_handle()
{
	if(_num_handles_allocated != NULL)
		*_num_handles_allocated = *_num_handles_allocated + 1;
}


void void_d_ptr::delete_unused_memory()
{
	if(*_num_handles_allocated == 0)
	{
		delete _ptr;
		_ptr = NULL;

		delete _num_handles_allocated;
		_num_handles_allocated = NULL;
	}
}


}