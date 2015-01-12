#include "shader_pass.h"

namespace deuterium
{
	ShaderPass::ShaderPass(ShaderComponent& vertex,ShaderComponent& fragment)
{
	_shader._handle = 0;


	//Update the shader components
	_shader._vertex_component	= vertex;
	_shader._fragment_component = fragment;
}


ShaderPass::~ShaderPass(void)
{
}


void ShaderPass::bind_material(const Material& m)
{
	m.bind_material();
}


bool ShaderPass::compile_components()
{

	//Compile both components
	_shader._vertex_component.compile();
	_shader._fragment_component.compile();

	return true;
}


void ShaderPass::compile(U32 id)
{
	//compile the components we an updated uniform buffer
	this->compile_components();

	if(_shader._handle)
			glDeleteProgram(_shader._handle);

		//Create the program and bind the shaders to it
		_shader._handle = glCreateProgram();

		
		//Attach the vertex shader
		_shader._vertex_component.attach_to_shader(_shader._handle);

		//Attach the fragment shader
		_shader._fragment_component.attach_to_shader(_shader._handle);


		
		//Bind Vertex component attributes
		_shader._vertex_component.bind_shader_attribute(_shader._handle);
		
		glLinkProgram(_shader._handle);

}



void ShaderPass::begin_pass()
{
	//Set shader
	glUseProgram(_shader._handle);

	//set sampler states, TODO

	
}


void ShaderPass::end_pass()
{
	//reset sampler states?

	//Unbind Program
	glUseProgram(0);
}

}
