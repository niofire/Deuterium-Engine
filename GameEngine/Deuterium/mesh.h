#pragma once
#include "global_data.h"
#include "index_buffer_container.h"
#include "vertex_buffer_container.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
/*
 * Contains all mesh information + One vao + vbos
 */
namespace deuterium
{
class Mesh
{
public:
	//-------------------------------------------------------------------
	//						Constructor / Destructor
	//-------------------------------------------------------------------
							Mesh();
	virtual					~Mesh();

	//-------------------------------------------------------------------
	//						Core Functions
	//-------------------------------------------------------------------
	virtual void			load_mesh(const char* filePath);
	//-------------------------------------------------------------------
	//						Accessors / Mutators
	//-------------------------------------------------------------------
	inline	bool						is_mesh_initialized()		{return _vao_handle != 0;};
	inline	VertexBufferContainer*		vertex_buffer_ptr()				{return &_vertex_buffer_container;};
	inline	IndexBufferContainer*		index_buffer_ptr()				{return &_index_buffer_container;};
	
protected:

	//-------------------------------------------------------------------
	//						Variable declaration
	//-------------------------------------------------------------------
	GLuint					_vao_handle;
	bool					m_BIsLoaded;
	VertexBufferContainer	_vertex_buffer_container;
	IndexBufferContainer	_index_buffer_container;
};
}


