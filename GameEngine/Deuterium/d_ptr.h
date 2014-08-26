#pragma once
#define NULL 0
#include <iostream>
/* The dPtr class
 *
 *
 *
 *
*/

#define dPtr_CAST(Type,var) *((dPtr<Type>*)&var);
template <class T>
class dPtr
	{
	public:
		dPtr(void);

		//constructor + allocate memory
		dPtr(T* ptr);

		//copy constructor
		dPtr(const dPtr&);

		//removes all references and update the number of handles
		~dPtr(void);

		//Allocate a memory location to the dPtr.
		void alloc(T* ptr);

		//Debug function
		//int* get_num_handle_ptr() { return _num_handles_allocatedPtr;}

		//Clears the pointer's reference and updates the number of handles
		void clear();

		bool is_null() { return _ptr == NULL;}
		int num_handles() { return _num_handles_allocatedPtr == NULL ?  0 :  *_num_handles_allocatedPtr;}
		//------------------------------------------------
		//			Operators
		//------------------------------------------------
		dPtr	&operator=(dPtr &ptr) {	
			this->clear();
			//update the num of allocated handles
			this->_num_handles_allocatedPtr = ptr._num_handles_allocatedPtr;
			this->add_handle();
	
			this->_ptr = ptr._ptr;
			return *this;
		};

		T& value() 
		{
			return *_ptr;
		}




		T*	operator->() const  {
			return _ptr;
		};


	private:
		void delete_unused_memory();
		void add_handle();
		int* _num_handles_allocatedPtr;
		T* _ptr;
};

template <class T>
dPtr<T>::dPtr()
{
	_num_handles_allocatedPtr = NULL;
	_ptr = NULL;

}

template <class T>
dPtr<T>::dPtr(T* ptr)
{
	_num_handles_allocatedPtr = NULL;
	_ptr = NULL;

	alloc(ptr);
}
template <class T>
dPtr<T>::dPtr(const dPtr& ptr)
{
	this->_ptr = NULL;
	this->_num_handles_allocatedPtr = NULL;

	//update the num of allocated handles
	this->_num_handles_allocatedPtr = ptr._num_handles_allocatedPtr;
	this->add_handle();
	
	this->_ptr = ptr._ptr;
}

template <class T>
dPtr<T>::~dPtr()
{
	this->clear();
}

template <class T>
void dPtr<T>::alloc(T* ptr)
{
	//clear previous reference
	this->clear();

	//store the newly allocated pointer
	_num_handles_allocatedPtr = new int(1);
	_ptr = ptr;
}


template <class T>
void dPtr<T>::clear()
{
	if(this->_num_handles_allocatedPtr != NULL)
	{
		*_num_handles_allocatedPtr = *_num_handles_allocatedPtr - 1;
		this->delete_unused_memory();
	}

	this->_ptr = NULL;
	this->_num_handles_allocatedPtr = NULL;
}

template <class T>
void dPtr<T>::add_handle()
{
	if(_num_handles_allocatedPtr != NULL)
		*_num_handles_allocatedPtr = *_num_handles_allocatedPtr + 1;
}

template <class T>
void dPtr<T>::delete_unused_memory()
{
	if(*_num_handles_allocatedPtr == 0)
	{
		delete _ptr;
		_ptr = NULL;

		delete _num_handles_allocatedPtr;
		_num_handles_allocatedPtr = NULL;
	}
}