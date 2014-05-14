#pragma once
#include "global_data.h"
#include "buffer_container.h"
#include <vector>



//
//
// TODO Pass by GPU in order to resize VBO (Create a static buffer which gets data copied to whenever resizing)

namespace deuterium
{

class StreamData;

class VertexBufferContainer : public BufferContainer
{
public:
	//--------------------------------------------------------------
	//					constructor / destructor
	//--------------------------------------------------------------
	VertexBufferContainer();
	virtual ~VertexBufferContainer();

	//--------------------------------------------------------------
	//					 Core Functions
	//--------------------------------------------------------------
	S32					add_stream(U32 i_Type);
	//Locks Vertex buffer container, preparing it to receive data
	void				lock_buffer(void** DataPtr,U32 i_StreamNumber,U32 i_Offset, U32 i_ByteSize);

	//Unlocks the buffer container, no longer allowing data entry
	void				unlock_buffer();

	//
	void				begin_render();
	
	//
	void				end_render();

	bool				has_element(U32 i_StreamNumber, U32 i_StreamComponents);

	void				reset();

	U32					stream_count()	{return _stream_list.size();}

	void				update_declaration();

	StreamData&			GetStreamData(U32 l_StreamNumber) {return _stream_list[l_StreamNumber];}

	void				delete_buffer();

private:
	static StreamData*			s_currently_locked_vertex_buffer;
	std::vector<StreamData>		_stream_list;
	bool						m_IsIndexBufferObjectUsed;
};



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