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



	//----------------------------------------------------
	//				Constructor / destructor
	//----------------------------------------------------
	ShaderParameter(std::string i_ParameterType, std::string i_ParameterName,GLint i_UniformLocation);
	ShaderParameter(const ShaderParameter& param);
	ShaderParameter();
	~ShaderParameter();

	void						update_cached_parameter(void* i_Value);
	void						bind_parameter_to_bound_program();

	//----------------------------------------------------
	//				Accessors
	//----------------------------------------------------
	const char*					name() {return _name.c_str();}
	DeuteriumPrimitiveType		type()	{return _type;}
	void*						value()	{return	_value;}
	S32							uniform_location()	{return _uniform_location;	}
	ShaderSemantic				shader_semantic()	{return _semantic_id;}
	void						set_uniform_location(S32 uniform_location) { _uniform_location = uniform_location;}
private:
	std::string				_name;
	DeuteriumPrimitiveType	_type;
	void*					_value;
	S32						_uniform_location;
	bool					_has_cached_value;
	ShaderSemantic				_semantic_id;
};
}