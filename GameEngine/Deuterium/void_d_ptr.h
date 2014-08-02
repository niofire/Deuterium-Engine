#pragma once
#define NULL 0
#include <iostream>
/* The d_ptr class
 *
 *
 *
 *
*/
namespace deuterium
{
class void_d_ptr
	{
	public:
		void_d_ptr(void);

		//constructor + allocate memory
		void_d_ptr(void* ptr);

		//copy constructor
		void_d_ptr(const void_d_ptr&);

		//removes all references and update the number of handles
		~void_d_ptr(void);

		//Allocate a memory location to the low_d_ptr.
		void alloc(void* ptr);

		//Debug function
		//int* get_num_handle_ptr() { return _num_handles_allocatelow_d_ptr;}

		//Clears the pointer's reference and updates the number of handles
		void clear();

		void* get_void_ptr() { return _ptr;}
		bool is_null() { return _ptr == NULL;}
		int num_handles() { return _num_handles_allocated == NULL ?  0 :  *_num_handles_allocated;}
		//------------------------------------------------
		//			Operators
		//------------------------------------------------
		void_d_ptr	&operator=(void_d_ptr &ptr) {	
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