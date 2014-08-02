#include "shader_component.h"
#include <iostream>
#include <fstream>
#include "stream_data.h"

namespace deuterium
{
ShaderComponent::ShaderComponent()
{
	_component_handle = 0;
	_is_compiled = false;
}


ShaderComponent::~ShaderComponent(void)
{
}



void ShaderComponent::compile()
{
	if(_is_compiled)
		return;

	std::string l_shaderContent = "";

	//Add uniform buffer to shader content
//	l_shaderContent = this->_uniform_buffer.to_shader_content_string(this->_uniform_buffer.name());

	//Add shader extensions

	//add glsl shader content
/*	for(int i = 0; i < _data._shader_content_DA.size(); ++i)
	{
		l_shaderContent += _data._shader_content_DA[i] + "\n";
	}
	*/
	//compile it
	const char* l_sShaderContent = l_shaderContent.c_str();
	int length = strlen(l_sShaderContent);
	_component_handle = glCreateShader(_data._shader_type);
	glShaderSource(_component_handle,1, &l_sShaderContent,&length);
	glCompileShader(_component_handle);

	//Get Info Log for error logging
	int infoLogLength = 0;
	int maxLength = 0;
	glGetShaderiv(_component_handle,GL_INFO_LOG_LENGTH, &maxLength);
	std::vector<char> infoLog(maxLength);
	glGetShaderInfoLog(_component_handle,maxLength, &infoLogLength, &infoLog[0]);
	std::string temp = &infoLog[0];


	//Display Info Log
	if(_data._shader_type == GL_VERTEX_SHADER)
		std::cerr << "Vertex Shader:" << temp << std::endl;
	else if(_data._shader_type == GL_FRAGMENT_SHADER)
		std::cerr << "Fragment Shader:" << temp << std::endl;

	_is_compiled = true;

}


void ShaderComponent::delete_and_uncache()
{
	if(_component_handle)
		glDeleteShader(_component_handle);

}

void ShaderComponent::add_attribute_location(StreamType type, const char* name)
{
	U32 attrib_index = StreamData::get_attribute_index(type);
	if(attrib_index == -1)
		return;

	this->_data._attribute_location.push_back(AttributeLocation(attrib_index,name));
}

}