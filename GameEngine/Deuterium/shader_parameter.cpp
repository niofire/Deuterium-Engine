#include "shader_parameter.h"
#include "string_helper.h"
#include "primitive_type_helper.h"
#include "memory_manager.h"
#include <iostream>

namespace deuterium
{

ShaderParameter::ShaderParameter()
{
	_has_cached_value = false;
	_name = "";
	_type = DEUTERIUM_UNKNOWN;
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
	_value = MemoryManager::alloc_memory(_type,1);
	this->update_cached_parameter(param._value);
}

ShaderParameter::ShaderParameter(std::string i_Parameter_type, std::string i_Parameter_name, GLint i_uniform_location)
{
	_name = i_Parameter_name;
		
	_type = StringHelper::parse_string_for_type(i_Parameter_type);
	
	_value = MemoryManager::alloc_memory(_type,1);
	_uniform_location = i_uniform_location;
}

void	ShaderParameter::update_cached_parameter(void* i__value)
{
	//Store given data inside the void* value pointer
	if(PrimitiveTypeHelper::is_float_derived(_type))
	{
		for(U32 i = 0; i < PrimitiveTypeHelper::num_of_values(_type); ++i)
			((float*)_value)[i] = ((float*)i__value)[i];
	}

	else if(PrimitiveTypeHelper::is_integer_derived(_type))
	{
		for(U32 i = 0; i < PrimitiveTypeHelper::num_of_values(_type); ++i)
			((int*)_value)[i] = ((int*)i__value)[i];
	}

	else if(PrimitiveTypeHelper::is_double_derived(_type))
	{
		for(U32 i = 0; i < PrimitiveTypeHelper::num_of_values(_type); ++i)
			((double*)_value)[i] = ((double*)i__value)[i];
	}
	_has_cached_value = true;

}

void ShaderParameter::bind_parameter_to_bound_program()
{
	//Check if parameter is currently used in the shader
	if( _uniform_location == -1)
		return;
	switch( _type)
	{

	case DEUTERIUM_INT1:
		glUniform1i( _uniform_location,*(U32*) _value);
		break;
	case DEUTERIUM_FLOAT1:
		glUniform1fv( _uniform_location,1,(float*) _value);
		break;
	case DEUTERIUM_FLOAT2:
		glUniform2fv( _uniform_location,1,(float*) _value);
		break;
	case DEUTERIUM_FLOAT3:
		glUniform3fv( _uniform_location,1,(float*) _value);
		break;
	case DEUTERIUM_FLOAT4:
		glUniform4fv( _uniform_location,1,(float*) _value);
		break;
	case DEUTERIUM_MAT3:
		glUniformMatrix3fv( _uniform_location,1,GL_FALSE,(float*) _value);
		break;
	case DEUTERIUM_MAT4:
		for(int i = 0; i < 4; ++i)
		{
			std::cout << ((float*) _value)[i * 4] << " " << ((float*) _value)[i*4 + 1] << " " << ((float*) _value)[i*4 + 2] << " " << ((float*) _value)[i * 4 + 3] << std::endl;

		}
		std::cout << std::endl;
		glUniformMatrix4fv( _uniform_location,1,GL_FALSE,(float*) _value);
		break;
	case DEUTERIUM_DOUBLE1:
#ifndef EMSCRIPTEN
		glUniform1dv( _uniform_location,1,(double*) _value);
#endif
		break;
	}

}


}