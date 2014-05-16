#include "mesh_manager.h"
#include <iostream>
#include "string_helper.h"

namespace deuterium
{

MeshManager::MeshManager()
{

}

MeshManager::~MeshManager()
{

}

Mesh&		MeshManager::add_existing_mesh(U32& o_Id, char* i_sMeshName, Mesh& i_Mesh)
{
	U32 Id = _mesh_container.add(MeshData(i_Mesh,0,i_sMeshName));
	_mesh_container.get_at(Id)->set_id(Id);
	return i_Mesh;
}

Mesh&		MeshManager::add_new_mesh(U32& o_Id, char* i_sMeshName)
{
	o_Id = _mesh_container.add(MeshData(Mesh(),0,i_sMeshName));
	_mesh_container.get_at(o_Id)->set_id(o_Id);
	return _mesh_container.get_at(o_Id)->mesh();
}

Mesh&		MeshManager::add_and_load_new_mesh(U32& o_Id, char* i_sMeshName, char* mesh_file_name)
{
	o_Id = _mesh_container.add(MeshData(Mesh(),0,i_sMeshName));
	
	_mesh_container.get_at(o_Id)->set_id(o_Id);
	_mesh_container.get_at(o_Id)->mesh().load_mesh(mesh_file_name);
	return _mesh_container.get_at(o_Id)->mesh();
}


void	MeshManager::remove_mesh(const U32& i_Id)
{
	_mesh_container.remove_at(i_Id);
}

MeshData* MeshManager::mesh_data_by_name(const char* i_sMeshName)
{
	
	_mesh_container.reset_iterator();
	MeshData* l_MeshDataTemp;
	while(l_MeshDataTemp = _mesh_container.iterator_next())
	{
		if(StringHelper::is_identical_string(l_MeshDataTemp->name(),i_sMeshName))
			return l_MeshDataTemp;
	}
	return NULL;
}
MeshData*	MeshManager::mesh_data_by_id(const U32& i_Id)
{
	if(_mesh_container.validate_id(i_Id))
		return _mesh_container.get_at(i_Id);
	return NULL;
}


Mesh* MeshManager::mesh_by_name(const char* i_MeshName)
{
	MeshData* mData = this->mesh_data_by_name(i_MeshName);
	if(!mData)
		return NULL;
	return &(mData->mesh());
}

Mesh* MeshManager::mesh_by_id(const U32& i_MeshId)
{
	MeshData* mData = mesh_data_by_id(i_MeshId);
	if(!mData)
		return NULL;
	return &(mData->mesh());
}
}