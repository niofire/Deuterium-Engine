#pragma once
#define NULL 0
#include <iostream>
/* The d_ptr class
 *
 *
 *
 *
*/

template <class T>
class d_ptr
	{
	public:
		d_ptr(void);

		//constructor + allocate memory
		d_ptr(T* ptr);

		//copy constructor
		d_ptr(d_ptr&);

		//removes all references and update the number of handles
		~d_ptr(void);

		//Allocate a memory location to the d_ptr.
		void alloc(T* ptr);

		//Clears the pointer's reference and updates the number of handles
		void clear();

		int num_handles() { return _num_handles_allocated_ptr == NULL ?  0 :  *_num_handles_allocated_ptr;}
		//------------------------------------------------
		//			Operators
		//------------------------------------------------
		d_ptr	&operator=(d_ptr &ptr) {	
			this->clear();
			//update the num of allocated handles
			this->_num_handles_allocated_ptr = ptr._num_handles_allocated_ptr;
			this->add_handle();
	
			this->_ptr = ptr._ptr;
			return *this;
		};

		T*	operator->() const  {
			return _ptr;
		};

	private:
		void delete_unused_memory();
		void add_handle();
		int* _num_handles_allocated_ptr;
		T* _ptr;
};

template <class T>
d_ptr<T>::d_ptr()
{
	_num_handles_allocated_ptr = NULL;
	_ptr = NULL;

}

template <class T>
d_ptr<T>::d_ptr(T* ptr)
{
	_num_handles_allocated_ptr = NULL;
	_ptr = NULL;

	alloc(ptr);
}
template <class T>
d_ptr<T>::d_ptr(d_ptr& ptr)
{
	this->_ptr = NULL;
	this->_num_handles_allocated_ptr = NULL;

	//update the num of allocated handles
	this->_num_handles_allocated_ptr = ptr._num_handles_allocated_ptr;
	this->add_handle();
	
	this->_ptr = ptr._ptr;
}

template <class T>
d_ptr<T>::~d_ptr()
{
	this->clear();
}

template <class T>
void d_ptr<T>::alloc(T* ptr)
{
	//clear previous reference
	this->clear();

	//store the newly allocated pointer
	_num_handles_allocated_ptr = new int(1);
	_ptr = ptr;
}


template <class T>
void d_ptr<T>::clear()
{
	if(this->_num_handles_allocated_ptr != NULL)
	{
		*_num_handles_allocated_ptr = *_num_handles_allocated_ptr - 1;
		this->delete_unused_memory();
	}

	this->_ptr = NULL;
	this->_num_handles_allocated_ptr = NULL;
}

template <class T>
void d_ptr<T>::add_handle()
{
	*_num_handles_allocated_ptr = *_num_handles_allocated_ptr + 1;
}

template <class T>
void d_ptr<T>::delete_unused_memory()
{
	if(*_num_handles_allocated_ptr == 0)
	{
		delete _ptr;
		_ptr = NULL;

		delete _num_handles_allocated_ptr;
		_num_handles_allocated_ptr = NULL;
	}
}