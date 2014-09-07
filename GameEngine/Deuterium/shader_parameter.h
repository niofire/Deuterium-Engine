#pragma once
#include <string>
#include "global_data.h"
#include "uniform_type_handler.h"

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
	ShaderParameter(DeuteriumUniformType type,U32 num_of_values, std::string name);
	ShaderParameter(const ShaderParameter& param);
	ShaderParameter();
	~ShaderParameter();

	void						update_cached_parameter(const void* i_Value);
	void						bind_parameter_to_bound_program();
	void						allocate_cache_memory();

	//----------------------------------------------------
	//				Accessors
	//----------------------------------------------------
	const char*					name() {return _name.c_str();}
	void						set_name(const char* name) { _name = name;}
	DeuteriumUniformType		type()	{return _type;}
	void						set_type(DeuteriumUniformType type) { _type = type;}
	void*						value()	{return	_value.get_voidPtr();}
	S32							uniform_location()	{return _uniform_location;	}
	bool						is_identical(const ShaderParameter& param);
	void						set_uniform_location(S32 uniform_location) { _uniform_location = uniform_location;}
private:
	std::string				_name;
	DeuteriumUniformType	_type;
	U32						_num_of_values;
	void_dPtr				_value;
	S32						_uniform_location;
};
}