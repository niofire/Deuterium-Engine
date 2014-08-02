#include "shader_parameter_value_settings.h"
namespace deuterium
{
ShaderParameterValueSettings::ShaderParameterValueSettings(void)
{
	_pass_id = 0;
}


ShaderParameterValueSettings::~ShaderParameterValueSettings(void)
{
}

/*
void	ShaderParameterValueSettings::bind_values_to_shader(U32 shader_handle)
{
	if(_last_bound_shader_handle != shader_handle) 
		update_shader_parameter_declaration(shader_handle);
	glUseProgram(shader_handle);

	for(U32 i =0 ; i < _shader_parameter_value_node_DA.size(); ++i)
	{
		_shader_parameter_value_node_DA[i].bind_parameter_to_bound_program();
	}
	glUseProgram(0);
}*/
/*
void ShaderParameterValueSettings::update_shader_parameter_declaration(ShaderTechnique* shader_technique)
{
	for(int i = 0; i < shader_technique->total_number_of_pass(); ++i)
	{
		ShaderPass* pass = shader_technique->get_pass(i);
		Shader* shader = pass->bound_shader();

		ObjectContainer<ShaderParameter>::Iterator iterator = shader->_shader_parameter_list.get_iterator();
		

		while(iterator.has_next())
		{
			ShaderParameter* shader_parameter = iterator.next();

			ShaderParameter parameter = ShaderParameter(*shader_parameter);
			
			this->_shader_parameter_value_DA[i].push_back(parameter);
			
			this->_shader_semantic_mapping.res



	}
	//if a new shader handle is passed, check for common parameter and update their location + add new shader parameter

	_last_bound_shader_handle = shader_handle;
	Shader new_shader = g_data._shader_manager_ptr->GetShader(shader_handle);

	ObjectContainer<ShaderParameter>::Iterator iterator = new_shader._shader_parameter_list.get_iterator();

	if(_shader_parameter_value_node_DA.size() > 0)
	{
		
		while(iterator.has_next())
		{
			ShaderParameter* shader_parameter = iterator.next();

			//Check for a common parameter

			bool is_common = false;
			for(int i = 0 ; i < _shader_parameter_value_node_DA.size(); ++i)
			{
				//found a common parameter
				if(StringHelper::is_identical_string(shader_parameter->name(),_shader_parameter_value_node_DA[i].name()))
				{
					//update uniform location
					_shader_parameter_value_node_DA[i].set_uniform_location(
						glGetUniformLocation(shader_handle,_shader_parameter_value_node_DA[i].name()));
					is_common = true;
				}
			}

			//if parameter is not common, add it to the array
			if(!is_common)
			{
				ShaderParameter parameter = ShaderParameter(*shader_parameter);
				
				this->_shader_parameter_value_node_DA.push_back(parameter);
			}
		}
		return;
	}

	//if assigning a new ShaderParameterValueSettings to a shader
	if(_shader_parameter_value_node_DA.size() == 0)
	{
		while(iterator.has_next())
		{
			ShaderParameter* shader_parameter = iterator.next();
			
			ShaderParameter parameter = ShaderParameter(*shader_parameter);
			
			this->_shader_parameter_value_node_DA.push_back(parameter);
		}

	}
}

bool	ShaderParameterValueSettings::update_value(char* parameter_name, void* value)
{

	for(U32 i = 0; i < _shader_parameter_value_node_DA.size();++i)
	{
		if(StringHelper::is_identical_string(parameter_name,_shader_parameter_value_node_DA[i].name()))
			{
				_shader_parameter_value_node_DA[i].update_cached_parameter(value);
				return true;
			}
		
	}
	return false;
}

	bool	ShaderParameterValueSettings::update_value(U32   index, void* value)
	{
		_shader_parameter_value_node_DA[ index ].update_cached_parameter(value);
	}

	U32		ShaderParameterValueSettings::parameter_index(char* parameter_name)
	{
		for(U32 i = 0 ; i < _shader_parameter_value_node_DA.size(); ++i)
		{
			if(StringHelper::is_identical_string(_shader_parameter_value_node_DA[ i ].name(),parameter_name))
				return i;
		}
		return 0;
	}

	const char*	ShaderParameterValueSettings::parameter_name(U32 index)
	{
		if(index > _shader_parameter_value_node_DA.size())
			return "";
		return _shader_parameter_value_node_DA[ index ] .name();
	}
*/


}