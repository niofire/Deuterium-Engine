#include "shader_parameter.h"
#include "string_helper.h"
#include "primitive_type_helper.h"
#include "memory_manager.h"
#include <iostream>

namespace deuterium
{

ShaderParameter::ShaderParameter()
{
	_parameter_data._id = UNKNOWN;
	_parameter_data._name = "";
	_parameter_data._type = DEUTERIUM_UNKNOWN;
	_parameter_data._uniform_location = -1;
}
ShaderParameter::~ShaderParameter()
{

}

ShaderParameter::ShaderParameter(const ShaderParameter& param)
{
	_parameter_data._id = UNKNOWN;
	
	_parameter_data._name = param._parameter_data._name;
		
	_parameter_data._type = param._parameter_data._type;

	_parameter_data._uniform_location = param._parameter_data._uniform_location;
	_parameter_data._value = MemoryManager::alloc_memory(_parameter_data._type,1);
}

ShaderParameter::ShaderParameter(std::string i_Parameter_type, std::string i_Parameter_name, GLint i_uniform_location)
{
	_parameter_data._id = UNKNOWN;
	_parameter_data._name = i_Parameter_name;
		
	_parameter_data._type = StringHelper::parse_string_for_type(i_Parameter_type);
	
	_parameter_data._value = MemoryManager::alloc_memory(_parameter_data._type,1);
	_parameter_data._uniform_location = i_uniform_location;
}

void				ShaderParameter::update_parameter(void* i__value)
{
	if(PrimitiveTypeHelper::is_float_derived(_parameter_data._type))
	{
		for(U32 i = 0; i < PrimitiveTypeHelper::num_of_values(_parameter_data._type); ++i)
			((float*)_parameter_data._value)[i] = ((float*)i__value)[i];
	}
	else if(PrimitiveTypeHelper::is_integer_derived(_parameter_data._type))
	{
		for(U32 i = 0; i < PrimitiveTypeHelper::num_of_values(_parameter_data._type); ++i)
			((int*)_parameter_data._value)[i] = ((int*)i__value)[i];
	}
	else if(PrimitiveTypeHelper::is_double_derived(_parameter_data._type))
	{
		for(U32 i = 0; i < PrimitiveTypeHelper::num_of_values(_parameter_data._type); ++i)
			((double*)_parameter_data._value)[i] = ((double*)i__value)[i];
	}

}

void ShaderParameter::update_program_parameter()
{
	//Check if parameter is currently used in the shader
	if(_parameter_data._uniform_location == -1)
		return;
	switch(_parameter_data._type)
	{

	case DEUTERIUM_INT1:
		glUniform1i(_parameter_data._uniform_location,*(U32*)_parameter_data._value);
		break;
	case DEUTERIUM_FLOAT1:
		glUniform1fv(_parameter_data._uniform_location,1,(float*)_parameter_data._value);
		break;
	case DEUTERIUM_FLOAT2:
		glUniform2fv(_parameter_data._uniform_location,1,(float*)_parameter_data._value);
		break;
	case DEUTERIUM_FLOAT3:
		glUniform3fv(_parameter_data._uniform_location,1,(float*)_parameter_data._value);
		break;
	case DEUTERIUM_FLOAT4:
		glUniform4fv(_parameter_data._uniform_location,1,(float*)_parameter_data._value);
		break;
	case DEUTERIUM_MAT3:
		glUniformMatrix3fv(_parameter_data._uniform_location,1,GL_FALSE,(float*)_parameter_data._value);
		break;
	case DEUTERIUM_MAT4:
		for(int i = 0; i < 4; ++i)
		{
			std::cout << ((float*)_parameter_data._value)[i * 4] << " " << ((float*)_parameter_data._value)[i*4 + 1] << " " << ((float*)_parameter_data._value)[i*4 + 2] << " " << ((float*)_parameter_data._value)[i * 4 + 3] << std::endl;

		}
		std::cout << std::endl;
		glUniformMatrix4fv(_parameter_data._uniform_location,1,GL_FALSE,(float*)_parameter_data._value);
		break;
	case DEUTERIUM_DOUBLE1:
#ifndef EMSCRIPTEN
		glUniform1dv(_parameter_data._uniform_location,1,(double*)_parameter_data._value);
#endif
		break;
	}

}


}