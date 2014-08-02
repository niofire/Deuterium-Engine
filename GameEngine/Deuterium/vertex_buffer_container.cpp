#include "vertex_buffer_container.h"
#include "index_buffer_container.h"
#include <iostream>
#include <cstdlib>

namespace deuterium
{

	StreamData* VertexBufferContainer::s_currently_locked_vertex_buffer = 0;

VertexBufferContainer::VertexBufferContainer()
{
	reset();
}

void VertexBufferContainer::reset()
{
	//TODO
}

VertexBufferContainer::~VertexBufferContainer()
{
}

void VertexBufferContainer::lock_buffer(void** o_data_ptr,U32 stream_number,U32 offset, U32 i_ByteSize)
{
	if(s_currently_locked_vertex_buffer)
		return;

	StreamData& stream_data = GetStreamData(stream_number);

	s_currently_locked_vertex_buffer = &stream_data;

	glBindBuffer(GL_ARRAY_BUFFER,stream_data.GetVbo());

	//Resize Vbo if it is too small
	void* dataPtr = 0;
	if( offset + i_ByteSize > stream_data.GetBufferByteSize())
	{
		//glGetBufferSubData(GL_ARRAY_BUFFER,0,i_Offset,dataPtr);
		glBufferData(GL_ARRAY_BUFFER,(offset + i_ByteSize),dataPtr,GL_STATIC_DRAW);
		stream_data.SetBufferByteSize(offset + i_ByteSize);
	}

#ifdef EMSCRIPTEN
	*o_data_ptr = new char[l_sData.GetBufferByteSize()];
	if(dataPtr)
		memcpy(*o_data_ptr,dataPtr,l_sData.GetBufferByteSize());
#else
	*o_data_ptr = glMapBufferRange(GL_ARRAY_BUFFER,offset,i_ByteSize,GL_MAP_WRITE_BIT);
#endif

	stream_data.SetDataPtr(o_data_ptr);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

bool VertexBufferContainer::has_element(U32 i_StreamNumber,U32 stream_component)
{
	
	return _stream_list[i_StreamNumber].ContainsStreamComponents(stream_component);
}

void VertexBufferContainer::delete_buffer()
{
	for(U32 i = 0; i < _stream_list.size();++i)
	{
		glDeleteBuffers(GL_ARRAY_BUFFER,&(_stream_list[i].GetVbo()));
	}
}

void VertexBufferContainer::unlock_buffer()
{
	if(!s_currently_locked_vertex_buffer)
		return;
	StreamData* l_sData = s_currently_locked_vertex_buffer;
	glBindBuffer(GL_ARRAY_BUFFER,l_sData->GetVbo());
	
	#ifdef EMSCRIPTEN
	glBufferData(GL_ARRAY_BUFFER,l_sData->GetBufferByteSize(),*l_sData->GetDataPtr(),GL_STATIC_DRAW);
	#else
	glUnmapBuffer(GL_ARRAY_BUFFER);
	#endif
	glBindBuffer(GL_ARRAY_BUFFER,0);

	s_currently_locked_vertex_buffer = NULL;
}

S32 VertexBufferContainer::add_stream(U32 type)
{
	//Check if stream is already present
	for(U32 i = 0; i < _stream_list.size(); ++i)
	{
		if(_stream_list[i].ContainsStreamComponents(type))
			return -1;
	}
	_stream_list.push_back(StreamData(type));
	return _stream_list.size() - 1;
}


void VertexBufferContainer::begin_render()
{
	for(U32 i =0 ; i < _stream_list.size();++i)
	{

		_stream_list[i].BindAttributesToShader();
	}
}

void VertexBufferContainer::end_render()
{

}

}