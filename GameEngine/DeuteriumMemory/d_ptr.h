#pragma once
#define NULL 0
template <class T>
class d_ptr
	{
	public:
		d_ptr(void);
		d_ptr(T);
		d_ptr	&operator=(d_ptr &_ptr);
		void allocate_memory();
		~d_ptr(void);

	private:
		int* _num_handles_allocated;
		T* _ptr;
};

template <class T>
void d_ptr::allocate_memory()
{
	//checks if pointer had already a memory location alllocated
	if(_num_handles_allocated != NULL)
	{
		*_num_handles_allocated -= 1;
		if(_num_handles_allocated == 0)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}

	_num_handles_allocated = new int(1);
	
}

template <class T>
d_ptr<T>::d_ptr()
{
	_id = NULL;
	_ptr = NULL;

}

template <class T>
d_ptr<T>::~d_ptr()
{

}

template <class T>
d_ptr<T>::operator=(d_str& ptr)
{
	
}
