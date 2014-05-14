#pragma once
#include "mesh.h"
#include "object_container.h"

namespace deuterium
{
class MeshData;
class MeshManager
{
public:
	//----------------------------------------------------------------
	//						Structure declaration
	//----------------------------------------------------------------
	

public:
	//----------------------------------------------------------------
	//						Constructor / destructor
	//----------------------------------------------------------------
	MeshManager();
	virtual ~MeshManager();

	//----------------------------------------------------------------
	//						Core Functions
	//----------------------------------------------------------------
	Mesh&					add_existing_mesh(U32& o_MeshId, char* i_sMeshName, Mesh& i_Mesh);
	Mesh&					add_new_mesh(U32& o_Id,char* i_sMeshName);
	Mesh&					add_new_mesh(char* i_sMeshName);
	void					remove_mesh(const U32& Id);
	MeshData*				mesh_data_by_name(const char* i_sMeshName);
	Mesh*					mesh_by_name(const char* i_sMeshName);
	Mesh*					mesh_by_id(const U32& Id);
	MeshData*				mesh_data_by_id(const U32& i_Id);
		


private:
	ObjectContainer<MeshData>			_mesh_container;
	

};

class MeshData
	{
	public:
		MeshData(Mesh i_Mesh, U32 i_Id,char* i_sName)
		{
			_mesh		= i_Mesh;
			_id		= i_Id;
			_name		= i_sName;
		}
		virtual ~MeshData()
		{

		}

		void		set_mesh(Mesh& i_Mesh)		{ _mesh = i_Mesh;}
		Mesh&		mesh()					{ return _mesh;}
		const U32&	id()	const			{ return _id;} 
		void		set_id(const U32& id)	{ _id = id;}
		const char*	name()	const			{ return _name;}
		void		set_name(char* i_sName)		{ _name = i_sName;}

		friend class MeshManager_L;
	private:
		Mesh		_mesh;
		U32			_id;
		char*		_name;
	};
}