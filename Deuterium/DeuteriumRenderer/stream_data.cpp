#include "stream_data.h"
#include "string_helper.h"
namespace deuterium
{

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
	U32	StreamData::GetStreamComponentOffset(VertexAttributeType i_Type)
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

	U32	StreamData::GetStreamTypeByteSize(VertexAttributeType i_StreamType)
	{
		for(U32 i = 0; i < _stream_component_list.size();++i)
		{
			if(i_StreamType == _stream_component_list[i]._stream_type)
				return _stream_component_list[i]._byte_size;
		}

		//Stream does not exist error
		return 0;
	}

	U32 StreamData::get_attribute_index(VertexAttributeType type)
	{
		U32 i = 0;
		U32 t = type;
		if(type >= VertexAttributeType::NULL0)
			return -1;
		while(t)
		{
			t  = t >> 1;
			if(!t)
				return i;
			i++;
		}
	}

	VertexAttributeType StreamData::to_enum(const char* type)
	{
		std::string t_str(type);
		StringHelper::trim(t_str);
		for(int i = 1; i < VertexAttributeType::NULL0; i = i<<1)
		{
			if(StringHelper::is_identical_string(StreamData::to_string((VertexAttributeType)i),t_str))
			{
				return (VertexAttributeType)i;
			}
		}
		return VertexAttributeType::NULL0;
	}
	
	const char* StreamData::to_string(VertexAttributeType type)
	{
		switch(type)
		{
		case POSITION0	:
			return "POSITION0";
		case POSITION1	:	
			return "POSITION1";
		case COLOR		:
			return "COLOR";
		case NORMAL		:
			return "NORMAL";
		case TANGENT	:
			return "TANGENT";
		case TEXCOORD0	:
			return "TEXCOORD0";
		case TEXCOORD1	:
			return "TEXCOORD1";
		case TEXCOORD2	:
			return "TEXCOORD2";
		case TEXCOORD3	:
			return "TEXCOORD3";
		case TEXCOORD4	:
			return "TEXCOORD4";
		case TEXCOORD5	:
			return "TEXCOORD5";
		case TEXCOORD6	:
			return "TEXCOORD6";
		case TEXCOORD7	:
			return "TEXCOORD7";
		default: 
			return "UNKNOWN";
		}
	}
	
	const char* StreamData::get_primitive_glsl_type_string(VertexAttributeType type)
	{
		switch(type)
		{
		case POSITION0	:
			return "vec3";
		case POSITION1	:	
			return "vec3";
		case COLOR		:
			return "vec3";
		case NORMAL		:
			return "vec3";
		case TANGENT	:
			return "vec3";
		case TEXCOORD0	:
			return "vec2";
		case TEXCOORD1	:
			return "vec2";
		case TEXCOORD2	:
			return "vec2";
		case TEXCOORD3	:
			return "vec2";
		case TEXCOORD4	:
			return "vec2";
		case TEXCOORD5	:
			return "vec2";
		case TEXCOORD6	:
			return "vec2";
		case TEXCOORD7	:
			return "vec2";
		default: 
			return "UNKNOWN";
		}
	}


}