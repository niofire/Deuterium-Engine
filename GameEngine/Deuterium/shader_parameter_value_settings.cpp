#include "shader_parameter_value_settings.h"
#include "shader.h"
#include "shader_manager.h"
namespace deuterium
{
ShaderParameterValueSettings::ShaderParameterValueSettings(U32 shader_handle)
{

}


ShaderParameterValueSettings::~ShaderParameterValueSettings(void)
{
}


void	ShaderParameterValueSettings::bind_values_to_shader(U32 shader_handle)
{
	if(last_bound_shader_handle != shader_handle) 

	glUseProgram(shader_handle);

	for(U32 i =0 ; i < _shader_parameter_value_node_DA.size(); ++i)
	{
		_shader_parameter_value_node_DA[i]._parameter.bind_parameter_to_bound_program();
	}
	glUseProgram(0);
}

void ShaderParameterValueSettings::udpate_shader_parameter_declaration(U32 shader_handle)
{
	//if a new shader handle is passed, check for common parameter and update their location + add new shader parameter
	
	if(_shader_parameter_value_node_DA.size() > 0)
	{
		Shader new_shader = g_data._shader_manager_ptr->GetShader(shader_handle);

		ObjectContainer<ShaderParameter>::Iterator iterator = new_shader._shader_parameter_list.get_iterator();
		
		while(iterator.has_next())
		{
			ShaderParameter* shader_parameter = iterator.next();

			//Check for a common parameter
			U32 
			if(StringHelper::is_identical_string(shader_parameter->name()
		}

		//update uniform location for matching uniforms
		while(new_shader._shader_parameter_list.
		for(int i = 0; i < new_shader._shader_parameter_list.size();++i)
		{

		}
	}
	_parameter_and_value_DA.clear();
	_shader_id = i_ShaderId;
	Shader l_Shader = g_data._shader_manager_ptr->GetShader(_shader_id);
	//shader parameter 1  => m_Parameter...DA;
	l_Shader._shader_parameter_list.reset_iterator();

	ShaderParameter* l_sParam;
	ParameterAndValueNode l_PaVNode;

	while(l_sParam = l_Shader._shader_parameter_list.iterator_next())
	{
		l_PaVNode._parameter_id = l_Shader._shader_parameter_list.get_iterator_position();
		l_PaVNode._parameter = ShaderParameter(*l_sParam);
		_parameter_and_value_DA.push_back(l_PaVNode);
	}
}

bool	ShaderParameterValueSettings::update_value(char* parameter_name, void* value)
{

	for(U32 i = 0; i < _shader_parameter_value_node_DA.size();++i)
	{
		if(StringHelper::is_identical_string(parameter_name,_shader_parameter_value_node_DA[i]._parameter.name()))
			{
				_shader_parameter_value_node_DA[i]._parameter.update_cached_parameter(value);
				return true;
			}
		
	}
	return false;
}

	bool	ShaderParameterValueSettings::update_value(U32   parameter_id, void* value)
	{
		_shader_parameter_value_node_DA[ parameter_id ] . _parameter.update_cached_parameter(value);
	}

	U32		ShaderParameterValueSettings::parameter_id(char* parameter_name)
	{
		for(U32 i = 0 ; i < _shader_parameter_value_node_DA.size(); ++i)
		{
			if(StringHelper::is_identical_string(_shader_parameter_value_node_DA[ i ]._parameter.name(),parameter_name))
				return _shader_parameter_value_node_DA[ i ] . _parameter_id;
		}
		return 0;
	}

	const char*	ShaderParameterValueSettings::parameter_name(U32 parameter_id)
	{
		if(parameter_id > _shader_parameter_value_node_DA.size())
			return "";
		return _shader_parameter_value_node_DA[ parameter_id ] . _parameter.name();
	}



}