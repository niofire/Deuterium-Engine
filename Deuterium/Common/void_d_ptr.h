#pragma once
#define NULL 0
#include <iostream>
/* The dPtr class
 *
 *
 *
 *
*/
namespace deuterium
{
class void_dPtr
	{
	public:
		void_dPtr(void);

		//constructor + allocate memory
		void_dPtr(void* ptr);

		//copy constructor
		void_dPtr(const void_dPtr&);

		//removes all references and update the number of handles
		~void_dPtr(void);

		//Allocate a memory location to the low_dPtr.
		void alloc(void* ptr);

		//Debug function
		//int* get_num_handle_ptr() { return _num_handles_allocatelow_dPtr;}

		//Clears the pointer's reference and updates the number of handles
		void clear();

		void* get_voidPtr() { return _ptr;}
		bool is_null() { return _ptr == NULL;}
		int num_handles() { return _num_handles_allocated == NULL ?  0 :  *_num_handles_allocated;}
		//------------------------------------------------
		//			Operators
		//------------------------------------------------
		void_dPtr	&operator=(void_dPtr &ptr) {	
			this->clear();
			//update the num of allocated handles
			this->_num_handles_allocated= ptr._num_handles_allocated;
			this->add_handle();
	
			this->_ptr = ptr._ptr;
			return *this;
		};

	private:
		void delete_unused_memory();
		void add_handle();
		int* _num_handles_allocated;
		void* _ptr;
};

}