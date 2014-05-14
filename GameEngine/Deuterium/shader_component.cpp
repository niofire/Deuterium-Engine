#include "shader_component.h"
#include <iostream>
#include <fstream>


namespace deuterium
{
ShaderComponent::ShaderComponent(void)
{
	_component_handle = 0;
	_shader_filename = "";
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

	for(int i = 0; i < _shader_content.size(); ++i)
	{
		l_shaderContent += _shader_content[i] + "\n";
	}

	//Get the shader code and compile it
	const char* l_sShaderContent = l_shaderContent.c_str();
	int length = strlen(l_sShaderContent);
	GLuint _component_handle = glCreateShader(_shader_type);
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

	if(temp.size() > 0)
	{
		std::cerr << "File Path:"	<< _shader_filename << std::endl;
	}
	if(_shader_type == GL_VERTEX_SHADER)
		std::cerr << "Vertex Shader:" << temp << std::endl;
	else if(_shader_type == GL_FRAGMENT_SHADER)
		std::cerr << "Fragment Shader:" << temp << std::endl;

	_is_compiled = true;

}


void ShaderComponent::load_by_content(GLenum i_shaderType, char* i_shaderContent)
{
	std::string shaderText = i_shaderContent;

	//Load content of shader files into shaderText
	_shader_type= i_shaderType;
	_shader_filename = "";
	std::vector<std::string> l_strVec = StringHelper::split(i_shaderContent,'\n');

	for(int i =0 ; i < l_strVec.size(); ++i)
	{
		_shader_content.push_back(l_strVec[i]);
	}
}

void ShaderComponent::load_by_file(GLenum i_shaderType,char* i_shaderFilepath)
{

	std::ifstream fileIn(i_shaderFilepath);
	if(!fileIn)
	{
		std::cerr << "Cannot open " << i_shaderFilepath << std::endl;
		return;
		exit(1);
	}
	std::string shaderText = "";

	//Load content of shader files into shaderText

	_shader_type= i_shaderType;
	_shader_filename = i_shaderFilepath;

	while(!fileIn.eof())
	{
		std::string temp = "";
		std::getline(fileIn, temp);
		_shader_content.push_back(temp);
	}
	fileIn.close();

}

void ShaderComponent::delete_and_uncache()
{
	if(_component_handle)
		glDeleteShader(_component_handle);

}

}