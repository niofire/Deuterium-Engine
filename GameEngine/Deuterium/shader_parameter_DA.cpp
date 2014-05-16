#include "shader_parameter_DA.h"
#include "shader.h"
#include "global_data.h"


namespace deuterium
{
ShaderParameterDA::ShaderParameterDA()
{
	_shader_id= 0;
}


ShaderParameterDA::~ShaderParameterDA()
{

}

void ShaderParameterDA::update_shader_parameter_declaration(U32 i_ShaderId)
{
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

void ShaderParameterDA::clean_parameters(U32 shader_id)
{
	//store parameter value in shader
	Shader s = g_data._shader_manager_ptr->GetShader(shader_id);
	for(int i = 0; i < _parameter_and_value_DA.size();++i)
	{
		ShaderParameter& s_param = _parameter_and_value_DA[i]._parameter;
		s.update_parameter(s_param.name(),s_param.value());
	}
}


void ShaderParameterDA::dirty_parameter(char* i_ParamName, void* value)
{
	for(U32 i = 0; i < _parameter_and_value_DA.size();++i)
	{
		if(StringHelper::is_identical_string(i_ParamName,_parameter_and_value_DA[i]._parameter.name()))
		{

			_parameter_and_value_DA[i]._parameter.update_parameter(value);
			return;
		}
	}
}

void ShaderParameterDA::update_parameter(ShaderParameter::SemanticId i_ParamId,void* value)
{
	for(U32 i = 0; i < _parameter_and_value_DA.size();++i)
	{
		if(i_ParamId == _parameter_and_value_DA[i]._parameter.semantic_id())
		{
			_parameter_and_value_DA[i]._parameter.update_parameter(value);
			return;
		}
	}
}

void	ShaderParameterDA::update_shader()
{
	Shader l_Shader = g_data._shader_manager_ptr->GetShader(_shader_id);

	for(U32 i = 0; i < _parameter_and_value_DA.size();++i)
	{
		
		//implement mechanism blocking shader updating when no value has never been inserted
			l_Shader._shader_parameter_list.get_at(_parameter_and_value_DA[i]._parameter_id)->
			update_parameter(_parameter_and_value_DA[i]._parameter.value());
			
	}
}
}