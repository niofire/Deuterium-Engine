#pragma once
#define NULL 0
#define NEW(x,y) x.allocate_memory(new y);

template <class T>
class d_ptr
	{
	public:
		d_ptr(void);
		
		void allocate_memory(T* ptr);
		~d_ptr(void);



		//------------------------------------------------
		//			Operators
		//------------------------------------------------
		d_ptr<T>	&operator=(d_ptr &_ptr) {	
				//update the num of allocated handles
				this->_num_handles_allocated_ptr = ptr._num_handles_allocated_ptr;
				*_num_handles_allocated_ptr += 1;
	
				this->_ptr = ptr._ptr;
				return *this;
			};


	private:
		void delete_unused_memory();
		int* _num_handles_allocated_ptr;
		T* _ptr;
};

template <class T>
void d_ptr<T>::allocate_memory(T* ptr)
{
	//checks if pointer had already a memory location allocated
	if(_num_handles_allocated_ptr != NULL)
	{
		*_num_handles_allocated_ptr -= 1;
		this->delete_unused_memory();
	}

	//store the newly allocated pointer
	_num_handles_allocated_ptr = new int(1);
	_ptr = ptr;
}

template <class T>
d_ptr<T>::d_ptr()
{
	_num_handles_allocated_ptr = NULL;
	_ptr = NULL;

}


template <class T>
void d_ptr<T>::delete_unused_memory()
{
	if(*_num_handles_allocated_ptr == 0)
	{
		delete _ptr;
		_ptr = NULL;
	}
}

template <class T>
d_ptr<T>::~d_ptr()
{
	*_num_handles_allocated_ptr -= 1;
	this->delete_unused_memory();

}
