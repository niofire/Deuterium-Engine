#include "shader_technique.h"

namespace deuterium
{
ShaderTechnique::ShaderTechnique(void)
{
	_current_pass = 0;
}

ShaderTechnique::ShaderTechnique(const char* name)
{
	_technique_name = name;
}


ShaderTechnique::~ShaderTechnique(void)
{
}

void ShaderTechnique::set_name(const char* name)
{
	_technique_name = name;
}

void ShaderTechnique::set_starting_pass(U32 pass_number)
{
	_current_pass = pass_number;
}


void ShaderTechnique::set_next_pass()
{
	_shader_pass_list[_current_pass]->end_pass();

	_current_pass++;

	if(has_remaining_pass())
	{
		_shader_pass_list[_current_pass]->begin_pass();
	}
}

ShaderPass* ShaderTechnique::get_pass(U32 pass_number)
{
	if(pass_number < _shader_pass_list.size())
	{
		return _shader_pass_list[pass_number];
	}
	return NULL;
}

ShaderParameterValueSettings	ShaderTechnique::get_parameter_value_settings()
{

}

}
