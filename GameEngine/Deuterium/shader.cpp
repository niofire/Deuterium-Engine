#include "shader.h"
#include <fstream>
#include <iostream>
#include "shader_parameter_DA.h"

namespace deuterium
{
Shader::Shader()
{
	_gl_shader_handle = 0;
	_number_of_textures_in_pass = 0;
	_shader_name = "";
	_shader_semantic_mapping.resize(ShaderParameter::NUMBER_OF_SEMANTIC,0);
}

Shader::~Shader()
{

}

void 	Shader::load_by_file(GLenum i_ShaderType, char* i_ShaderPath)
{
	ShaderComponent temp;
	temp.load_by_file(i_ShaderType,i_ShaderPath);
	_shader_component_list.push_back(temp);
}

void Shader::load_by_content(GLenum i_ShaderType, char* i_ShaderContent)
{
	ShaderComponent temp;
	temp.load_by_content(i_ShaderType,i_ShaderContent);
	_shader_component_list.push_back(temp);
}

void 	Shader::compile()
{
		if(_gl_shader_handle)
			glDeleteProgram(_gl_shader_handle);

		//Create the program and bind the shaders to it
		_gl_shader_handle = glCreateProgram();

		std::cout << "Compiling Shader: " << _shader_name << std::endl;
		for(U32 i = 0; i < _shader_component_list.size(); ++i)
		{
			_shader_component_list[i].compile();

			glAttachShader(_gl_shader_handle,_shader_component_list[i].component_handle());
		}

		//Link the program and delete sub-programs
		update_shader_attribute_binding();
		
		glLinkProgram(_gl_shader_handle);
	
		update_shader_parameter_declaration();

}






void Shader::update_shader_attribute_binding()
{
	glBindAttribLocation(_gl_shader_handle,0,"position0");
	glBindAttribLocation(_gl_shader_handle,1,"position1");
	glBindAttribLocation(_gl_shader_handle,2,"color");
	glBindAttribLocation(_gl_shader_handle,3,"normal");
	glBindAttribLocation(_gl_shader_handle,4,"tangent");
	glBindAttribLocation(_gl_shader_handle,5,"texcoord0");
	glBindAttribLocation(_gl_shader_handle,6,"texcoord1");
	glBindAttribLocation(_gl_shader_handle,7,"texcoord2");
	glBindAttribLocation(_gl_shader_handle,8,"texcoord3");
	glBindAttribLocation(_gl_shader_handle,9,"texcoord4");
	glBindAttribLocation(_gl_shader_handle,10,"texcoord5");
	glBindAttribLocation(_gl_shader_handle,11,"texcoord6");
	glBindAttribLocation(_gl_shader_handle,11,"texcoord7");
}
void Shader::update_shader_parameter_declaration()
{

	//Parse through all active shader components
	for(U32 i = 0 ;i < _shader_component_list.size(); ++i)
	{
		//Parse through content of shader file
		for(U32 j = 0; j < _shader_component_list[i].component_content().size(); ++j)
		{
			std::string l_CurrentString = _shader_component_list[i].component_content()[j];

			//if string contains a uniform
			if(l_CurrentString.find("uniform") != std::string::npos)
			{
				//Example string, uniform vec3 myVarName;
				
				std::string l_UniformTypeString = l_CurrentString.substr(l_CurrentString.find("uniform") + 7);
				StringHelper::trim_front(l_UniformTypeString);

				
				l_UniformTypeString = l_UniformTypeString.substr(0,l_UniformTypeString.find(" "));
				StringHelper::trim(l_UniformTypeString);


				//contains uniform name
				std::string l_UniformNameString = l_CurrentString.substr(l_CurrentString.find(l_UniformTypeString) + l_UniformTypeString.length());
				StringHelper::trim_front(l_UniformNameString);
				l_UniformNameString = l_UniformNameString.substr(0,l_UniformNameString.find(" ") == std::string::npos ?
					l_UniformNameString.find(";") : l_UniformNameString.find(" "));
				StringHelper::trim(l_UniformNameString);
				



				
				//Check if uniform is a semantic
				
				//add ShaderParameter to list
				_shader_parameter_list.add(new ShaderParameter(l_UniformTypeString,l_UniformNameString,glGetUniformLocation(_gl_gl_shader_handle,l_UniformNameString.c_str())));

				
			}

		}
	}

}


void Shader::begin_render()
{
	glUseProgram(_gl_shader_handle);
}

void Shader::end_render()
{
	glUseProgram(0);
	_number_of_textures_in_pass = 0;
}

ShaderParameterValueSettings Shader::get_shader_parameter_value_settings()
{
	ShaderParameterValueSettings s;
	s.update_shader_parameter_declaration(this->shader_handle);
	return s;
}
void	Shader::bind_shader_parameter_value_settings(ShaderParameterValueSettings* param)
{
	param->bind_values_to_shader(this->_gl_shader_handle);
}

}

