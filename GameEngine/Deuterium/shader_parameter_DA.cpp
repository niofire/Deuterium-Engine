#include "shader_parameter_DA.h"
#include "shader_parameter.h"
#include "shader.h"
#include "global_data.h"
#include "string_helper.h"
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
	Shader l_Shader = gData._shader_manager_ptr->GetShader(_shader_id);
	//shader parameter 1  => m_Parameter...DA;
	l_Shader._shader_parameter_list.reset_iterator();

	ShaderParameter* l_sParam;
	ParameterAndValueNode l_PaVNode;
	while(l_sParam = l_Shader._shader_parameter_list.iterator_next())
	{
		l_PaVNode._parameter_id = l_Shader._shader_parameter_list._iterator_position();
		l_PaVNode._parameter = *l_sParam;
		_parameter_and_value_DA.push_back(l_PaVNode);
	}
}


void ShaderParameterDA::update_parameter(char* i_ParamName, void* value)
{
	for(U32 i = 0; i < _parameter_and_value_DA.size();++i)
	{
		if(StringHelper::is_identical_string(i_ParamName,_parameter_and_value_DA[i]._parameter.GetParameterName()))
		{
			_parameter_and_value_DA[i]._parameter.UpdateParameter(value);
			return;
		}
	}
}

void ShaderParameterDA::update_parameter(ShaderParameter::SemanticId i_ParamId,void* value)
{
	for(U32 i = 0; i < _parameter_and_value_DA.size();++i)
	{
		if(i_ParamId == _parameter_and_value_DA[i]._parameter.GetShaderParameterId())
		{
			_parameter_and_value_DA[i]._parameter.UpdateParameter(value);
			return;
		}
	}
}

void	ShaderParameterDA::update_shader()
{
	Shader l_Shader = gData._shader_manager_ptr->GetShader(_shader_id);

	for(U32 i = 0; i < _parameter_and_value_DA.size();++i)
	{
		if(_parameter_and_value_DA[i]._parameter.IsParameterInitialized())
			l_Shader._shader_parameter_list.get_at(_parameter_and_value_DA[i]._parameter_id)->
			UpdateParameter(_parameter_and_value_DA[i]._parameter.GetParameterValue());
	}
}
}