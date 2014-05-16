#pragma once
#include <string>
#include "global_data.h"


namespace deuterium
{
class ShaderParameter
{
public:
	//----------------------------------------------------
	//				struct/enum
	//----------------------------------------------------
	enum SemanticId
	{
		WORLDVIEW = 0,
		WORLDVIEWPROJ,
		TEXTURESAMPLER,
		NORMALSAMPLER,
		TIME,
		UNKNOWN,
	};

	
	struct ParameterData
	{
		std::string				_name;
		SemanticId				_id;
		DeuteriumPrimitiveType	_type;
		void*					_value;
		S32						_uniform_location;
	};


	//----------------------------------------------------
	//				Constructor / destructor
	//----------------------------------------------------
	ShaderParameter(std::string i_ParameterType, std::string i_ParameterName,GLint i_UniformLocation);
	ShaderParameter(const ShaderParameter& param);
	ShaderParameter();
	~ShaderParameter();

	void						update_parameter(void* i_Value);
	void						update_program_parameter();
	//----------------------------------------------------
	//				Accessors
	//----------------------------------------------------
	const char*					name() {return _parameter_data._name.c_str();}
	SemanticId					semantic_id() {return _parameter_data._id;}
	DeuteriumPrimitiveType		type()	{return _parameter_data._type;}
	void*						value()	{return	_parameter_data._value;}

private:
	ParameterData		_parameter_data;
};
}