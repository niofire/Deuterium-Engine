#pragma once
#include "buffer_container.h"
#include "global_data.h"

namespace deuterium
{

class IndexBufferContainer : public BufferContainer
{
public:
	IndexBufferContainer();
	virtual ~IndexBufferContainer();

	//--------------------------------------------------------------
	//					 Core Functions
	//--------------------------------------------------------------
	
	void				lock_buffer(void** data_ptr,U32 offset, U32 byte_size);

	void				unlock_buffer();

	U32					ibo()			{return _ibo_handle;}

	void				begin_render();

	void				end_render();

	U32					num_elements()	{return _index_buffer_byte_size/sizeof(U16);	}

	void				reset();

	void				delete_buffer();
private:
	U32 _ibo_handle;

	U32	_index_buffer_byte_size;

	static void* s_data_ptr;
};

}