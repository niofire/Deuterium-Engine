#include "shader_pass.h"
#include "shader_manager.h"

namespace deuterium
{
ShaderPass::ShaderPass(void)
{
}


ShaderPass::~ShaderPass(void)
{
}


void ShaderPass::begin_pass()
{
	//Bind values to shader
	_param_value_settings->bind_values_to_shader(_shader->gl_shader_handle());

	//Set shader
	glUseProgram(_shader->gl_shader_handle());

	//set sampler states, TODO

	
}

void ShaderPass::end_pass()
{
	//reset sampler states?

	glUseProgram(0);
}

}