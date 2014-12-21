#include "material.h"

namespace deuterium
{


	Material::Material()
	{
	}


	Material::~Material()
	{
	}

	//-----------------------------------------------------
	//				Material Operations
	//-----------------------------------------------------
	void	Material::bind_material()
	{

	}
	void	Material::unbind_material()
	{

	}

	//-----------------------------------------------------
	//				ShaderParameter Operations
	//-----------------------------------------------------
	ShaderParameter* Material::get_parameter_by_name(const char* name)
	{
		std::string s_name(name);

		//if name matches, return
		for (U32 i = 0; i < _parameterDA.size(); ++i)
		{
			if (s_name.compare(_parameterDA[i].name()) == 0)
				return &_parameterDA[i];
		}
		
		return NULL;
	}
	ShaderParameter* Material::get_parameter_by_id(const U32& id)
	{
		//check for ID overflow
		if (id >= _parameterDA.size())
			return NULL;

		return &_parameterDA[id];
	}

	//Add a shader parameter to the material. 
	void Material::add_shader_parameter(ShaderParameter p)
	{
		_parameterDA.push_back(p);
	}


	//----------------------------------------------------
	//				Texture Operations
	//----------------------------------------------------
	void Material::add_texture(U32 texture_handle)
	{

	}
}