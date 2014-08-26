#include "void_dPtr.h"

namespace deuterium
{

	
void_dPtr::void_dPtr()
{
	_num_handles_allocated = NULL;
	_ptr = NULL;

}


void_dPtr::void_dPtr(void* ptr)
{
	_num_handles_allocated = NULL;
	_ptr = NULL;

	alloc(ptr);
}

void_dPtr::void_dPtr(const void_dPtr& ptr)
{
	this->_ptr = NULL;
	this->_num_handles_allocated = NULL;

	//update the num of allocated handles
	this->_num_handles_allocated = ptr._num_handles_allocated;
	this->add_handle();
	
	this->_ptr = ptr._ptr;
}


void_dPtr::~void_dPtr()
{
	this->clear();
}


void void_dPtr::alloc(void* ptr)
{
	//clear previous reference
	this->clear();

	//store the newly allocated pointer
	_num_handles_allocated = new int(1);
	_ptr = ptr;
}

void void_dPtr::clear()
{
	if(this->_num_handles_allocated != NULL)
	{
		*_num_handles_allocated = *_num_handles_allocated - 1;
		this->delete_unused_memory();
	}

	this->_ptr = NULL;
	this->_num_handles_allocated = NULL;
}


void void_dPtr::add_handle()
{
	if(_num_handles_allocated != NULL)
		*_num_handles_allocated = *_num_handles_allocated + 1;
}


void void_dPtr::delete_unused_memory()
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