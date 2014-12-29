#include "shader_component.h"
#include "stream_data.h"
#include <iostream>
#include <fstream>
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


void ShaderComponent::load(std::vector<std::string>& file_contentDA)
{
	std::string attribute_tag	= "attribute";
	std::string uniform_tag		= "uniform";

	//Parse through the shader content and retrieve all uniforms/attribute
	for(int i = 0; i < file_contentDA.size(); ++i)
	{
		file_contentDA[i].

	}
}
void ShaderComponent::compile()
{
	if(_is_compiled)
		return;

	std::string l_shaderContent = "";
	
	//Add the included extension source 
	for(int i = 0; i < this->_data._shader_extension_DA.size(); ++i)
	{
		l_shaderContent += _data._shader_extension_DA[i]->extension() + "\n";
	}

	//Add the predefined uniform buffer 
	for(int i = 0; i < this->_data._constant_uniform_buffer_DA.size(); ++i)
	{
		l_shaderContent += _data._constant_uniform_buffer_DA[i]->to_shader_code() + "\n";
	}

	//Add the dynamic uniform buffer
	l_shaderContent += _data._dynamic_uniform_buffer->to_shader_code() + "\n";

	//Add the attributes
	for(int i = 0; i < this->_data._attribute_location_DA.size(); ++i)
	{
		std::string attribute_str = "attribute ";
		attribute_str += std::string(StreamData::get_primitive_glsl_type_string((StreamType)_data._attribute_location_DA[i]._attrib_stream_type)) + " " ;
		attribute_str += _data._attribute_location_DA[i]._attrib_name + ";";
		l_shaderContent += attribute_str + "\n";
	}

	//Add the shader source code
	l_shaderContent += _data._shader_content;

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

void ShaderComponent::bind_shader_attribute(U32 shader_handle)
{
	for(int i = 0; i < _data._attribute_location_DA.size(); ++i)
	{
		S32 attr_loc= StreamData::get_attribute_index((StreamType)_data._attribute_location_DA[i]._attrib_stream_type);
		const char* attr_name = _data._attribute_location_DA[i]._attrib_name.c_str();
		if(attr_loc != -1)
			glBindAttribLocation(shader_handle,attr_loc,attr_name);
	}
}

void ShaderComponent::add_attribute_location(StreamType type, const char* name)
{
	U32 attrib_index = StreamData::get_attribute_index(type);
	if(attrib_index == -1)
	{
		dErrorStack::get_instance().push(dError("Attribute"));
		return;
	}
	
	this->_data._attribute_location_DA.push_back(AttributeLocation(type,name));
}

void ShaderComponent::attach_to_shader(const U32& handle)
{
	glAttachShader(handle,_component_handle);
}

}


