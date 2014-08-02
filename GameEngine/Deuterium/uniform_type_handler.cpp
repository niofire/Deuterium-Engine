#include "uniform_type_handler.h"

namespace deuterium
{
	
	UniformTypeHandler::UniformTypeData UniformTypeHandler::_uniform_type_data_array[NUMBER_OF_DEUTERIUM_UNIFORM_TYPE]=	{
		UniformTypeHandler::UniformTypeData("int", 1, sizeof(int), D_INT),
		UniformTypeHandler::UniformTypeData("uint", 1, sizeof(unsigned int), D_UINT),
		UniformTypeHandler::UniformTypeData("float", 1, sizeof(float), D_FLOAT),
		UniformTypeHandler::UniformTypeData("vec2", 2, sizeof(float), D_VEC2),
		UniformTypeHandler::UniformTypeData("vec3", 3, sizeof(float), D_VEC3),
		UniformTypeHandler::UniformTypeData("vec4", 4, sizeof(float), D_VEC4),
		UniformTypeHandler::UniformTypeData("ivec2", 2, sizeof(int), D_IVEC2),
		UniformTypeHandler::UniformTypeData("ivec3", 3, sizeof(int), D_IVEC3),
		UniformTypeHandler::UniformTypeData("ivec4", 4, sizeof(int), D_IVEC4),
		UniformTypeHandler::UniformTypeData("uvec2", 2, sizeof(unsigned int), D_UIVEC2),
		UniformTypeHandler::UniformTypeData("uvec3", 3, sizeof(unsigned int), D_UIVEC3),
		UniformTypeHandler::UniformTypeData("uvec4", 4, sizeof(unsigned int), D_UIVEC4),
		UniformTypeHandler::UniformTypeData("mat2", 4, sizeof(float), D_MAT2),
		UniformTypeHandler::UniformTypeData("mat3", 9, sizeof(float), D_MAT3),
		UniformTypeHandler::UniformTypeData("mat4", 16, sizeof(float), D_MAT4),
	};
	


void_d_ptr UniformTypeHandler::alloc_memory(DeuteriumUniformType type,const U32& num)
{
	return void_d_ptr(malloc(num * UniformTypeHandler::size_of(type) * UniformTypeHandler::num_of_values(type))); 

}
std::string UniformTypeHandler::to_string(DeuteriumUniformType type)
{
	return _uniform_type_data_array[type]._name;
}
DeuteriumUniformType UniformTypeHandler::to_enum(const std::string& str)
{
	for(U32 i = 0 ;i < UniformTypeHandler::num_of_uniform_types();++i)	
	{
		if(StringHelper::is_identical_string(str,_uniform_type_data_array[i]._name))
		{
			return (DeuteriumUniformType)i;
		}
		
	}
	return D_UNKNOWN_UNIFORM_TYPE;
}
const U32&		UniformTypeHandler::num_of_values(DeuteriumUniformType type)
{
	if(type >= num_of_uniform_types())
		return 0;
	return _uniform_type_data_array[type]._num_values;
}
const U32&		UniformTypeHandler::size_of(DeuteriumUniformType type)
{
	if(type >= num_of_uniform_types())
		return 0;
	return _uniform_type_data_array[type]._byte_size;
}
bool	UniformTypeHandler::is_float_derived(DeuteriumUniformType type)
{
	switch(type)
	{
	case D_FLOAT:
	case D_VEC2:
	case D_VEC3:
	case D_VEC4:
	case D_MAT2:
	case D_MAT3:
	case D_MAT4:
		return true;
	default:
		return false;
	}
}
bool	UniformTypeHandler::is_integer_derived(DeuteriumUniformType type)
{
	switch(type)
	{
	case D_INT:
	case D_UINT:
	case D_IVEC2:
	case D_IVEC3:
	case D_IVEC4:
	case D_UIVEC2:
	case D_UIVEC3:
	case D_UIVEC4:
		return true;
	default:
		return false;
	}
		
}
}