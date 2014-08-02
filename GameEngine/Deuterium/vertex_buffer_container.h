#pragma once
#include "global_data.h"
#include "buffer_container.h"
#include "stream_data.h"
#include <vector>



//
//
// TODO Pass by GPU in order to resize VBO (Create a static buffer which gets data copied to whenever resizing)

namespace deuterium
{
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



}