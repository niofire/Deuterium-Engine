#include "shader_parameter.h"
#include "string_helper.h"

#include "primitive_type_handler.h"

namespace deuterium
{

ShaderParameter::ShaderParameter()
{
	_parameter_data._id = UNKNOWN;
	_parameter_data._name = "";
	_parameter_data._type = DEUTERIUM_UNKNOWN;
	_is_initialized = false;
}
ShaderParameter::~ShaderParameter()
{

}


ShaderParameter::ShaderParameter(std::string i_Parameter_type, std::string i_Parameter_name, GLint i__uniform_location)
{
	_is_initialized = false;
	//MAKE CLASS FOR _typeS
	//MALLOC FROM _type
	//TEST IN TESTCASE
	if(i_Parameter_name.find("pWorldViewProj") != std::string::npos)
	{
		_parameter_data._id = WORLDVIEWPROJ;
		_parameter_data._name = "pWorldViewProj";
		_parameter_data._type = LODE_MAT4;
	}
	else if(i_Parameter_name.find("pWorldView") != std::string::npos)
	{
		_parameter_data._id = WORLDVIEW;
		_parameter_data._name = "pWorldView";
		_parameter_data._type = LODE_MAT3;
	}
	else if(i_Parameter_name.find("pTextureSampler") != std::string::npos)
	{
		_parameter_data._id = TEXTURESAMPLER;
		_parameter_data._name = "pTextureSampler";
		_parameter_data._type = LODE_INT1;
	}
	else if(i_Parameter_name.find("pNormalSampler") != std::string::npos)
	{
		_parameter_data._id = NORMALSAMPLER;
		_parameter_data._name = "pNormalSampler";
		_parameter_data._type = LODE_INT1;
	}
	else if(i_Parameter_name.find("pTime") != std::string::npos)
	{
		_parameter_data._id = TIME;
		_parameter_data._name = "pTime";
		_parameter_data._type = LODE_FLOAT1;
	}
	else
	{
		_parameter_data._id = UNKNOWN;
		_parameter_data._name = i_Parameter_name;
		
		_parameter_data._type = StringHelper::parse_string_for_type(i_Parameter_type);
	}
	
	_parameter_data._value = gData._typeHandlerPtr->AllocMemory(_parameter_data._type);
	_parameter_data._uniform_location = i__uniform_location;
}

void				ShaderParameter::UpdateParameter(void* i__value)
{
	if(gData._typeHandlerPtr->IsFloatPrimitive(_parameter_data._type))
	{
		for(U32 i = 0; i < gData._typeHandlerPtr->GetNumberOf_values(_parameter_data._type); ++i)
			((float*)_parameter_data._value)[i] = ((float*)i__value)[i];
	}
	else if(gData._typeHandlerPtr->IsIntegerPrimitive(_parameter_data._type))
	{
		for(U32 i = 0; i < gData._typeHandlerPtr->GetNumberOf_values(_parameter_data._type); ++i)
			((int*)_parameter_data._value)[i] = ((int*)i__value)[i];
	}
	else if(gData._typeHandlerPtr->IsDoublePrimitive(_parameter_data._type))
	{
		for(U32 i = 0; i < gData._typeHandlerPtr->GetNumberOf_values(_parameter_data._type); ++i)
			((double*)_parameter_data._value)[i] = ((double*)i__value)[i];
	}
	_is_initialized = true;

}

void ShaderParameter::UpdateProgramParameter()
{
	if(!_is_initialized)
		return;
	U32 s = 0;
	switch(_parameter_data._type)
	{
	case LODE_INT1:
		s = *(U32*)_parameter_data._value;
		glUniform1i(_parameter_data._uniform_location,*(U32*)_parameter_data._value);
		break;
	case LODE_FLOAT1:
		glUniform1fv(_parameter_data._uniform_location,1,(float*)_parameter_data._value);
		break;
	case LODE_FLOAT2:
		glUniform2fv(_parameter_data._uniform_location,1,(float*)_parameter_data._value);
		break;
	case LODE_FLOAT3:
		glUniform3fv(_parameter_data._uniform_location,1,(float*)_parameter_data._value);
		break;
	case LODE_FLOAT4:
		glUniform4fv(_parameter_data._uniform_location,1,(float*)_parameter_data._value);
		break;
	case LODE_MAT3:
		glUniformMatrix3fv(_parameter_data._uniform_location,1,GL_FALSE,(float*)_parameter_data._value);
		break;
	case LODE_MAT4:
		glUniformMatrix4fv(_parameter_data._uniform_location,1,GL_FALSE,(float*)_parameter_data._value);
	case LODE_DOUBLE1:
#ifndef EMSCRIPTEN
		glUniform1dv(_parameter_data._uniform_location,1,(double*)_parameter_data._value);
#endif
		break;
	}

}


}