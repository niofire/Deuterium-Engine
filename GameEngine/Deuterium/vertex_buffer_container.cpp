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


//------------------------------------------------------------------
//					StreamData
//------------------------------------------------------------------

StreamData::StreamData(U32 i_StreamComponents)
{
	StreamComponent l_comp;
	l_comp._offset = 0;
	l_comp._stream_type = NULL0;
	l_comp._vertex_attribute_index = 0;
	l_comp._num_values = 0;
	l_comp._is_normalized = false;
	_stride = 0;
	_vbo_handle = 0;
	_stream_component = i_StreamComponents;
	_buffer_byte_size = 0;


	if(i_StreamComponents & POSITION0)
	{
		
		l_comp._stream_type = POSITION0;
		l_comp._vertex_attribute_index = 0;
		l_comp._num_values = 3;
		l_comp._type = GL_FLOAT;
		l_comp._byte_size = sizeof(float) * 3;
		_stream_component_list.push_back(l_comp);
		l_comp._offset += l_comp._byte_size;
		_stride += sizeof(float) * 3;
	}

	if(i_StreamComponents & POSITION1)
	{

		l_comp._stream_type = POSITION1;
		l_comp._vertex_attribute_index = 1;
		l_comp._num_values = 3;
		l_comp._type = GL_FLOAT;
		l_comp._byte_size = sizeof(float) * 3;
		_stream_component_list.push_back(l_comp);
		l_comp._offset += l_comp._byte_size;
		_stride += sizeof(float) * 3;
	}
	if(i_StreamComponents & COLOR)
	{
		l_comp._stream_type = COLOR;
		l_comp._vertex_attribute_index = 2;
		l_comp._num_values = 3;
		l_comp._type = GL_FLOAT;
		l_comp._byte_size = sizeof(float) * 3;
		_stream_component_list.push_back(l_comp);
		l_comp._offset += l_comp._byte_size;
		_stride += sizeof(float) * 3;
	}
	if(i_StreamComponents & TANGENT)
	{
		l_comp._stream_type = TANGENT;
		l_comp._vertex_attribute_index = 3;
		l_comp._num_values = 3;
		l_comp._type = GL_FLOAT;
		l_comp._byte_size = sizeof(float) * 3;
		l_comp._offset += l_comp._byte_size;
		_stream_component_list.push_back(l_comp);
		_stride += sizeof(float) * 3;
	}
	if(i_StreamComponents & NORMAL)
	{
		l_comp._stream_type = POSITION0;
		l_comp._vertex_attribute_index = 4;
		l_comp._num_values = 3;
		l_comp._type = GL_FLOAT;
		l_comp._byte_size = sizeof(float) * 3;
		_stream_component_list.push_back(l_comp);
		l_comp._offset += l_comp._byte_size;
		_stride += sizeof(float) * 3;
	}
	for(int i = 0; i <7; ++i)
	{
		if(i_StreamComponents & (TEXCOORD0 << i))
		{
			
			l_comp._stream_type = (StreamType)(TEXCOORD0 << i);
			l_comp._vertex_attribute_index = 5 + i;
			l_comp._num_values = 2;
			l_comp._type = GL_FLOAT;
			l_comp._byte_size = sizeof(float) * 2;
			_stream_component_list.push_back(l_comp);
			l_comp._offset += l_comp._byte_size;
			_stride += sizeof(float) * 2;
		}
	}
	glGenBuffers(1,&_vbo_handle);
}

StreamData::~StreamData()
{

}
U32	StreamData::GetStreamComponentOffset(StreamType i_Type)
{
	for(U32 i = 0; i < _stream_component_list.size(); ++i)
	{
		if(_stream_component_list[i]._stream_type == i_Type)
			return _stream_component_list[i]._offset;
	}
	return StreamData::Invalid;
}

bool StreamData::ContainsStreamComponents(U32 i_StreamComponents)
{
	return (i_StreamComponents & _stream_component) == i_StreamComponents;
}

void StreamData::BindAttributesToShader()
{
	glBindBuffer(GL_ARRAY_BUFFER,_vbo_handle);
	for(U32 i =0 ; i < _stream_component_list.size(); ++i)
	{
		StreamComponent l_sComp = _stream_component_list[i];
		glEnableVertexAttribArray(l_sComp._vertex_attribute_index);
		U32 l_VertexStride = _stream_component_list.size() > 1 ? _stride : 0;
		glVertexAttribPointer(l_sComp._vertex_attribute_index,l_sComp._num_values,l_sComp._type,GL_FALSE,l_VertexStride,(void*)l_sComp._offset);
	}
	glBindBuffer(GL_ARRAY_BUFFER,NULL);
}

U32	StreamData::GetStreamTypeByteSize(StreamType i_StreamType)
{
	for(U32 i = 0; i < _stream_component_list.size();++i)
	{
		if(i_StreamType == _stream_component_list[i]._stream_type)
			return _stream_component_list[i]._byte_size;
	}

	//Stream does not exist error
	return 0;
}



}