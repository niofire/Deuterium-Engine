#include "shader_parameter.h"
#include "string_helper.h"
#include "memory_manager.h"
#include <iostream>

namespace deuterium
{

ShaderParameter::ShaderParameter()
{
	_num_of_values = 1;
	_name = "";
	_value = void_d_ptr();
	_type = D_UNKNOWN_UNIFORM_TYPE;
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
	_value = void_d_ptr();
	_num_of_values = param._num_of_values;
	void_d_ptr temp = param._value;
	if(temp.is_null())
		return;

	this->allocate_cache_memory();
	this->update_cached_parameter(temp.get_void_ptr());

}

ShaderParameter::ShaderParameter(DeuteriumUniformType type, U32 num_of_values, std::string name)
{
	_name = name;
	_type = type;
	_num_of_values = num_of_values;
}
bool ShaderParameter::is_identical(const ShaderParameter& param)
{
	return StringHelper::is_identical_string(_name,param._name) 
		&& _type == param._type;
}

void	ShaderParameter::update_cached_parameter(const void* i__value)
{
	if(_value.is_null())
		allocate_cache_memory();
	//Store given data inside the void* value pointer
	if(UniformTypeHandler::is_float_derived(_type))
	{
		for(U32 i = 0; i < UniformTypeHandler::num_of_values(_type); ++i)
			((float*)_value.get_void_ptr())[i] = ((float*)i__value)[i];
	}

	else if(UniformTypeHandler::is_integer_derived(_type))
	{
		for(U32 i = 0; i < UniformTypeHandler::num_of_values(_type); ++i)
			((int*)_value.get_void_ptr())[i] = ((int*)i__value)[i];
	}
	

}

void ShaderParameter::allocate_cache_memory()
{
	if(this->_value.is_null())
	{
		_value = UniformTypeHandler::alloc_memory(_type,_num_of_values);
	}
}

void ShaderParameter::bind_parameter_to_bound_program()
{
	//Check if parameter is currently used in the shader
	if( _uniform_location == -1)
		return;
	void* val = _value.get_void_ptr();
	switch( _type)
	{

	case D_INT:
		glUniform1i( _uniform_location,*(U32*) val);
		break;
	case D_FLOAT:
		glUniform1fv( _uniform_location,1,(float*) val);
		break;
	case D_VEC2:
		glUniform2fv( _uniform_location,1,(float*) val);
		break;
	case D_VEC3:
		glUniform3fv( _uniform_location,1,(float*) val);
		break;
	case D_VEC4:
		glUniform4fv( _uniform_location,1,(float*) val);
		break;
	case D_MAT3:
		glUniformMatrix3fv( _uniform_location,1,GL_FALSE,(float*) val);
		break;
	case D_MAT4:
		for(int i = 0; i < 4; ++i)
		{
			std::cout << ((float*) val)[i * 4] << " " << ((float*) val)[i*4 + 1] << " " << ((float*) val)[i*4 + 2] << " " << ((float*) val)[i * 4 + 3] << std::endl;

		}
		std::cout << std::endl;
		glUniformMatrix4fv( _uniform_location,1,GL_FALSE,(float*) val);
		break;
	}

}


}