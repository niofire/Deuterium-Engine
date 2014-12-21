#include "shader_parameter.h"
#include "string_helper.h"
#include <iostream>
#include "global_data.h"
namespace deuterium
{

ShaderParameter::ShaderParameter()
{
	_num_of_values = 1;
	_name = "";
	_type = UniformType::D_FLOAT;
	_uniform_location = -1;
}
ShaderParameter::~ShaderParameter()
{

}

ShaderParameter::ShaderParameter(const ShaderParameter& param)
{	
	_name = param._name;
	_type = param._type;
	_uniform_location = param._uniform_location;
	_num_of_values = param._num_of_values;


	void_dPtr temp = param._dataPtr;
	if(temp.is_null())
		return;

	//Allocate the memory for the current data pointer
	allocate_memory();

	//copy the values
	update(temp.get_voidPtr());
}

ShaderParameter::ShaderParameter(const char* name, UniformType type, U8 num_of_values, void* data)
{
	initialize(name, type, num_of_values, data);
}

void			ShaderParameter::initialize(const char* name, UniformType type, U8 num_of_values, void* data)
{
	_name = name;
	_type = type;
	_num_of_values = num_of_values;

	allocate_memory();
	
	
}

void ShaderParameter::allocate_memory()
{
	_byte_size = 0;
	switch (_type)
	{

	case UniformType::D_INT:
		_byte_size = sizeof(int);
		break;
	case UniformType::D_VEC2:
		_byte_size = sizeof(float)* 2;
		break;
	case UniformType::D_VEC3:
		_byte_size = sizeof(float)* 3;
		break;
	case UniformType::D_VEC4:
		_byte_size = sizeof(float)* 4;
		break;
	case UniformType::D_MAT3:
		_byte_size = sizeof(float)* 9;
		break;
	case UniformType::D_MAT4:
		_byte_size = sizeof(float)* 16;
		break;
	case UniformType::D_FLOAT:
		_byte_size = sizeof(float);
		break;
	case UniformType::D_DOUBLE:
		_byte_size = sizeof(double);
		break;
	}

	_dataPtr.alloc(_num_of_values * _byte_size);

}

void			ShaderParameter::update(void* data)
{
	if (_dataPtr.is_null())
		return;
	switch (_type)
	{
	case UniformType::D_INT:
		for (int i = 0; i < _num_of_values; ++i)
		{
			((int*)_dataPtr.get_voidPtr())[i] = ((int*)data)[i];
		}
		break;

	case UniformType::D_DOUBLE:
		for (int i = 0; i < _num_of_values; ++i)
		{
			((double*)_dataPtr.get_voidPtr())[i] = ((double*)data)[i];
		}
		break;
	case UniformType::D_MAT3:
	case UniformType::D_MAT4:
	case UniformType::D_VEC2:
	case UniformType::D_VEC3:
	case UniformType::D_VEC4:
	case UniformType::D_FLOAT:
		for (U32 i = 0; i < _num_of_values * (_byte_size /sizeof(float)); ++i)
		{
			((float*)_dataPtr.get_voidPtr())[i] = ((float*)data)[i];
		}
		break;
	}
}

void ShaderParameter::bind_to_shader(U32 shader_id)
{
	if (_shader_id != shader_id)
	{
		_shader_id = shader_id;
		_uniform_location = glGetUniformLocation(_shader_id, _name.c_str());
	}

	//Check if parameter is currently used in the shader
	if( _uniform_location == -1)
		return;
	void* val = _dataPtr.get_voidPtr();

	switch( _type)
	{	
	case D_INT:
		glUniform1i( _uniform_location,*(U32*) val);
		break;
	case D_FLOAT:
		glUniform1fv( _uniform_location,_num_of_values,(float*) val);
		break;
	case D_VEC2:
		glUniform2fv(_uniform_location, _num_of_values, (float*)val);
		break;
	case D_VEC3:
		glUniform3fv(_uniform_location, _num_of_values, (float*)val);
		break;
	case D_VEC4:
		glUniform4fv(_uniform_location, _num_of_values, (float*)val);
		break;
	case D_MAT3:
		glUniformMatrix3fv(_uniform_location, _num_of_values, GL_FALSE, (float*)val);
		break;
	case D_MAT4:
		/*for(int i = 0; i < 4; ++i)
		{
			std::cout << ((float*) val)[i * 4] << " " << ((float*) val)[i*4 + 1] << " " << ((float*) val)[i*4 + 2] << " " << ((float*) val)[i * 4 + 3] << std::endl;

		}
		std::cout << std::endl;
		*/
		glUniformMatrix4fv(_uniform_location, _num_of_values, GL_FALSE, (float*)val);
		break;
	}

}


}