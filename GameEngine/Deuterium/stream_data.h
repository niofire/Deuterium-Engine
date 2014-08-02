#pragma once
#include "global_data.h"
namespace deuterium
{
	
class StreamData
	{
	public:

		struct StreamComponent
		{
			StreamType		_stream_type;
			U32				_offset;
			U32				_vertex_attribute_index;
			U8				_num_values;
			GLenum			_type;
			GLboolean		_is_normalized;
			U32				_byte_size;

		};

		static const U8 Invalid = -1;
		StreamData(U32 stream_component);
		~StreamData();

		U32		GetStreamComponentOffset(StreamType stream_component);
		U32		GetStreamStride() {return _stride;}
		bool	ContainsStreamComponents(U32 stream_component);
		const U32&		GetVbo() const	{ return _vbo_handle;}
		U32		GetStreamTypeByteSize(StreamType stream_component);

		U32		GetBufferByteSize()	{return _buffer_byte_size;}
		void	SetBufferByteSize(U32 i_ByteSize)	{ _buffer_byte_size = i_ByteSize;}
		void	BindAttributesToShader();
		void**	GetDataPtr() {return _data_ptr;}
		void	SetDataPtr(void** i_DataPtr) { _data_ptr = i_DataPtr;}
		static StreamType to_enum(const char* str);
		static const char* to_string(StreamType type);
		static U32 get_attribute_index(StreamType type);
	private:
		void**		_data_ptr;
		U32			_buffer_byte_size;
		U32			_stream_component;
		U16			_num_components;
		U32			_stride;
		U32			_vbo_handle;

		std::vector<StreamComponent> _stream_component_list;

};

}

