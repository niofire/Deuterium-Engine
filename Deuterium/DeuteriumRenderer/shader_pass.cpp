#include "shader_pass.h"

namespace deuterium
{
	ShaderPass::ShaderPass(ShaderComponent& vertex_shader,ShaderComponent& fragment_shader)
{

	_shader_handle = 0;

	//Update the shader components
	this->_components._vertex_shader = vertex_shader;
	this->_components._fragment_shader = fragment_shader;

	//merge and re-allocate dynamic uniform buffer
	this->_uniform_buffer = UniformBuffer();
	_uniform_buffer.load_uniform_buffer(vertex_shader.get_dynamic_uniform_buffer().value());
	_uniform_buffer.load_uniform_buffer(fragment_shader.get_dynamic_uniform_buffer().value());
	

	//
	_shader_state = LOADED;
}


ShaderPass::~ShaderPass(void)
{
}

void ShaderPass::update_uniform_declaration()
{
	this->_uniform_buffer.clear_uniform_buffer();

	this->_uniform_buffer.load_uniform_buffer(this->_components._vertex_shader.get_dynamic_uniform_buffer().value());
	this->_uniform_buffer.load_uniform_buffer(this->_components._fragment_shader.get_dynamic_uniform_buffer().value());
	this->_uniform_buffer.set_name(this->name() + "_uBuffer");

}

bool ShaderPass::update_parameters(dPtr<ShaderParameterValueSettings> param_val_ptr)
{
	if(param_val_ptr->pass_id() != this->_shader_handle)
		return false;

	//Update this pass through the ShaderParameterValueSettings
	//TODO
	return true;
}

bool ShaderPass::compile_components()
{
	this->update_uniform_declaration();

	_components._vertex_shader.get_dynamic_uniform_buffer()->clear_uniform_buffer();
	_components._vertex_shader.get_dynamic_uniform_buffer()->load_uniform_buffer(this->_uniform_buffer);

	_components._fragment_shader.get_dynamic_uniform_buffer()->clear_uniform_buffer();
	_components._fragment_shader.get_dynamic_uniform_buffer()->load_uniform_buffer(this->_uniform_buffer);
	
	//compile components
	_components._vertex_shader.compile();
	_components._fragment_shader.compile();
	return true;
}
bool ShaderPass::compile_pass()
{
	if(_shader_state == COMPILED)
		return false;

	//compile the components we an updated uniform buffer
	this->compile_components();

	if(_shader_handle)
			glDeleteProgram(_shader_handle);

		//Create the program and bind the shaders to it
		_shader_handle = glCreateProgram();

		
		//Attach the vertex shader
		glAttachShader(_shader_handle,_components._vertex_shader.component_handle());

		//Attach the fragment shader
		glAttachShader(_shader_handle,_components._fragment_shader.component_handle());

		//Link the program and DELETE/TODO sub-programs
		this->_components._vertex_shader.bind_shader_attribute(this->_shader_handle);
		
		glLinkProgram(_shader_handle);

		_shader_state = COMPILED;
	return true;
}




dPtr<ShaderParameterValueSettings> ShaderPass::get_parameter_and_value_setting()
{	
	dPtr<ShaderParameterValueSettings> param_and_value_arr;
	if(_shader_state == COMPILED)
	{
		param_and_value_arr;
	}
	param_and_value_arr->_pass_id = this->_id;
	param_and_value_arr->_uniform_buffer = this->_uniform_buffer;

	return param_and_value_arr;

}

void ShaderPass::begin_pass()
{
	//Bind values to shader
	//_param_value_settings->bind_values_to_shader(_shader->gl_shader_handle());

	//Set shader
	//glUseProgram(_shader->gl_shader_handle());

	//set sampler states, TODO

	
}


void ShaderPass::end_pass()
{
	//reset sampler states?

	glUseProgram(0);
}

}

shader_pass::shader_pass(void)
{
}


shader_pass::~shader_pass(void)
{
}
