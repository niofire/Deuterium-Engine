#pragma once
#include <string>
#include "d_typedef.h"
#include "void_d_ptr.h"
namespace deuterium
{
class ShaderParameter
{
public:
	enum UniformType
	{
		D_INT,
		D_FLOAT,
		D_DOUBLE,
		D_VEC2,
		D_VEC3,
		D_VEC4,
		D_MAT3,
		D_MAT4,
	};
public:
	//----------------------------------------------------
	//				Constructor / destructor
	//----------------------------------------------------
	ShaderParameter(const ShaderParameter& param);
	ShaderParameter(const char* name, UniformType type, U8 num_of_values, void* data);
	ShaderParameter();
	~ShaderParameter();

	void			initialize(const char* name, UniformType type, U8 num_of_values, void* data);
	void			update(void* data);
	void			bind_to_shader(U32 shader_id);

	//----------------------------------------------------
	//				Accessors
	//----------------------------------------------------
	const char*					name() {return _name.c_str();}
	void						set_name(const char* name) { _name = name;}
	void*						value()	{return	_dataPtr.get_voidPtr();}
	
private:
	void			allocate_memory();
private:
	U32					_shader_id;
	std::string				_name;
	UniformType			_type;
	U8						_num_of_values;
	U8						_byte_size;
	void_dPtr				_dataPtr;
	S32						_uniform_location;
};
}