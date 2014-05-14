#include "shader.h"
#include <fstream>
#include <iostream>
#include "string_helper.h"
#include "shader_parameter_DA.h"

namespace deuterium
{
Shader::Shader()
{
	_shader_handle = 0;
	_number_of_textures_in_pass = 0;
	_shader_name = "";
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
		if(_shader_handle)
			glDeleteProgram(_shader_handle);

		//Create the program and bind the shaders to it
		_shader_handle = glCreateProgram();

		std::cout << "Compiling Shader: " << _shader_name << std::endl;
		for(int i = 0; i < _shader_component_list.size(); ++i)
		{
			_shader_component_list[i].compile();
			glAttachShader(_shader_handle,_shader_component_list[i].component_handle());
		}

		//Link the program and delete sub-programs
		update_shader_attribute_binding();
		
		glLinkProgram(_shader_handle);
	
		update_shader_parameter_declaration();

}

void	Shader::update_parameter(ShaderParameter::SemanticId i_Param,void* i_Value)
{
	m_ShaderParameterList.Iterator_Reset();
	ShaderParameter* l_ShaderParameter;
	while(l_ShaderParameter = m_ShaderParameterList.Iterator_Next())
	{
		if(l_ShaderParameter->GetShaderParameterId() == i_Param)
		{
			l_ShaderParameter->UpdateParameter(i_Value);
			return;
		}
	}
}

void	Shader::update_parameter(char* i_ParamName, void* i_Value)
{
	m_ShaderParameterList.Iterator_Reset();
	ShaderParameter* l_ShaderParameter;
	while(l_ShaderParameter = m_ShaderParameterList.Iterator_Next())
	{
		if(StringHelper_L::IsIdenticalString(l_ShaderParameter->GetParameterName(),i_ParamName))
		{
			l_ShaderParameter->UpdateParameter(i_Value);
		}
	}
}

void	Shader::update_parameter(ShaderParameterAndValueArray_L* i_ShaderParamAndValueArrayPtr)
{
	i_ShaderParamAndValueArrayPtr->UpdateShader();
}


void	Shader::bind_texture_to_sampler(char* i_ParamName, Texture_L* i_Texture)
{
	glActiveTexture(GL_TEXTURE0 + _number_of_textures_in_pass);
	glBindTexture(GL_TEXTURE_2D,i_Texture->GetTextureHandle());
	UpdateParameter(i_ParamName, &_number_of_textures_in_pass);
	_number_of_textures_in_pass++;
}

void Shader::bind_texture_to_sampler(ShaderParameter::SemanticId i_Param, Texture_L* i_Texture)
{
	glActiveTexture(GL_TEXTURE0 + _number_of_textures_in_pass);
	glBindTexture(GL_TEXTURE_2D,i_Texture->GetTextureHandle());
	UpdateParameter(i_Param, &_number_of_textures_in_pass);
	_number_of_textures_in_pass++;
}

void Shader::update_shader_attribute_binding()
{
	glBindAttribLocation(_shader_handle,0,"position0");
	glBindAttribLocation(_shader_handle,1,"position1");
	glBindAttribLocation(_shader_handle,2,"color");
	glBindAttribLocation(_shader_handle,3,"normal");
	glBindAttribLocation(_shader_handle,4,"tangent");
	glBindAttribLocation(_shader_handle,5,"texcoord0");
	glBindAttribLocation(_shader_handle,6,"texcoord1");
	glBindAttribLocation(_shader_handle,7,"texcoord2");
	glBindAttribLocation(_shader_handle,8,"texcoord3");
	glBindAttribLocation(_shader_handle,9,"texcoord4");
	glBindAttribLocation(_shader_handle,10,"texcoord5");
	glBindAttribLocation(_shader_handle,11,"texcoord6");
	glBindAttribLocation(_shader_handle,11,"texcoord7");
}
void Shader::update_shader_parameter_declaration()
{

	//Parse through all active shaders
	for(U32 i = 0 ;i < _shader_component_list.size(); ++i)
	{
		//Parse through content of shader file
		for(U32 j = 0; j < _shader_component_list[i].GetComponentContent().size(); ++j)
		{
			std::string l_CurrentString = _shader_component_list[i].GetComponentContent()[j];

			//if string contains a uniform
			if(l_CurrentString.find("uniform") != std::string::npos)
			{
				//string containing uniform type
				std::string l_UniformTypeString = l_CurrentString.substr(l_CurrentString.find("uniform") + 7);
				StringHelper_L::TrimFront(l_UniformTypeString);
				l_UniformTypeString = l_UniformTypeString.substr(0,l_UniformTypeString.find(" "));
				StringHelper_L::Trim(l_UniformTypeString);

				//string containing uniform name
				std::string l_UniformNameString = l_CurrentString.substr(l_CurrentString.find("uniform") + 7);
				StringHelper_L::TrimFront(l_UniformNameString);
				l_UniformNameString = l_UniformNameString.substr(l_UniformNameString.find(" "));
				l_UniformNameString = l_UniformNameString.substr(0,l_UniformNameString.find(";"));
				StringHelper_L::Trim(l_UniformNameString);

				//add ShaderParameter to list
				m_ShaderParameterList.AddObject(ShaderParameter(l_UniformTypeString,l_UniformNameString,glGetUniformLocation(_shader_handle,l_UniformNameString.c_str())));

			}

		}
	}

}
void Shader::update_shader_parameters()
{

	glUseProgram(_shader_handle);
	_shader_parameter_list.reset_iterator();
	
	ShaderParameter* l_ShaderParameter;
	while( l_ShaderParameter = _shader_parameter_list.iterator_next())
	{
		l_ShaderParameter->UpdateProgramParameter();
	}
	glUseProgram(0);
}


void Shader::begin_render()
{
	glUseProgram(_shader_handle);
}

void Shader::end_render()
{
	glUseProgram(0);
	_number_of_textures_in_pass = 0;
}
}