#include "index_buffer_container.h"
#include <cstdlib>

namespace deuterium
{
	void* IndexBufferContainer::s_data_ptr = NULL;

IndexBufferContainer::IndexBufferContainer()
	: BufferContainer()
{
	_index_buffer_byte_size = 0;
	glGenBuffers(1,&_ibo_handle);
}

IndexBufferContainer::~IndexBufferContainer()
{
}

void IndexBufferContainer::reset()
{
	_index_buffer_byte_size = 0;

	
	//Remove all elements present in the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ibo_handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,0,0,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void IndexBufferContainer::delete_buffer()
{
	glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER,&_ibo_handle);

}

void IndexBufferContainer::lock_buffer(void** o_data_ptr, U32 i_Offset, U32 i_ByteSize)
{
	if(s_data_ptr)
		return;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ibo_handle);

	void* t_data_ptr = 0;
	if( i_Offset + i_ByteSize > _index_buffer_byte_size)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,i_Offset,t_data_ptr,GL_STATIC_READ);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,(i_Offset + i_ByteSize),t_data_ptr,GL_STATIC_DRAW);
		_index_buffer_byte_size = i_Offset + i_ByteSize;
	}
	
#ifdef EMSCRIPTEN
	*o_data_ptr = malloc(m_IndexBufferByteSize);
	if(dataPtr)
		memcpy(*o_DataPtr,dataPtr,m_IndexBufferByteSize);
#else
	*o_data_ptr = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER,i_Offset,i_ByteSize,GL_MAP_WRITE_BIT);
#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	s_data_ptr = *o_data_ptr;
}

void IndexBufferContainer::unlock_buffer()
{
	if(!s_data_ptr)
		return;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ibo_handle);
	#ifdef EMSCRIPTEN
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,_index_buffer_byte_size ,s_data_ptr,GL_STATIC_DRAW);
	free(s_data_ptr);
	#else
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	s_data_ptr = NULL;

	//Free allocated memory
	
}

void IndexBufferContainer::begin_render()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ibo_handle);
}

void IndexBufferContainer::end_render()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
}