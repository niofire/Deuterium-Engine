#include "primitive_type_helper.h"

namespace deuterium
{

	
	bool PrimitiveTypeHelper::is_instantiated = false;
	PrimitiveTypeHelper::TypeData PrimitiveTypeHelper::_type_info[DEUTERIUM_UNKNOWN];

void PrimitiveTypeHelper::instantiate_handler()
{
	if(PrimitiveTypeHelper::is_instantiated)
		return;

	
	TypeData l_data;

	//INT1
	l_data._num_values = 1;
	l_data._size_of_primitive = sizeof(int);
	l_data._type = DEUTERIUM_INT1;
	_type_info[DEUTERIUM_INT1] = l_data;

	///DOUBLE1
	l_data._type = DEUTERIUM_DOUBLE1;
	l_data._size_of_primitive = sizeof(double);
	_type_info[DEUTERIUM_DOUBLE1] = l_data;

	//FLOAT1
	l_data._size_of_primitive = sizeof(float);
	l_data._type = DEUTERIUM_FLOAT1;
	_type_info[DEUTERIUM_FLOAT1] = l_data;

	//FLOAT2
	l_data._num_values = 2;
	l_data._type = DEUTERIUM_FLOAT2;
	_type_info[DEUTERIUM_FLOAT2] = l_data;

	//FLOAT3
	l_data._num_values = 3;
	l_data._type = DEUTERIUM_FLOAT3;
	_type_info[DEUTERIUM_FLOAT3] = l_data;

	//FLOAT4
	l_data._num_values = 4;
	l_data._type = DEUTERIUM_FLOAT4;
	_type_info[DEUTERIUM_FLOAT4] = l_data;

	//MAT3
	l_data._num_values = 9;
	l_data._type = DEUTERIUM_MAT3;
	_type_info[DEUTERIUM_MAT3] = l_data;

	//MAT4
	l_data._num_values = 16;
	l_data._type = DEUTERIUM_MAT4;
	_type_info[DEUTERIUM_MAT4] = l_data;


}

DeuteriumPrimitiveType PrimitiveTypeHelper::parse_string_for_type(std::string  str)
{
		if(str.find("vec4") != std::string::npos)
		return DEUTERIUM_FLOAT4;
	else if(str.find("vec3") != std::string::npos)
		return DEUTERIUM_FLOAT3;
	else if(str.find("vec2") != std::string::npos)
		return DEUTERIUM_FLOAT2;
	else if(str.find("float") != std::string::npos)
		return DEUTERIUM_FLOAT1;
	else if(str.find("int") != std::string::npos)
		return DEUTERIUM_INT1;
	else if(str.find("mat4") != std::string::npos)
		return DEUTERIUM_MAT4;
	else if(str.find("mat3") != std::string::npos)
		return DEUTERIUM_MAT3;
	
	return DEUTERIUM_UNKNOWN;

}

U32 PrimitiveTypeHelper::num_of_values(DeuteriumPrimitiveType i_Type)
{
	if(!is_instantiated)
		instantiate_handler();
	if(i_Type != DEUTERIUM_UNKNOWN)
		return _type_info[i_Type]._num_values;
	return 0;
}

U32 PrimitiveTypeHelper::size_of(DeuteriumPrimitiveType type)
{
	return _type_info[type]._size_of_primitive;

}

bool	PrimitiveTypeHelper::is_double_derived(DeuteriumPrimitiveType i_Type)
{
	if(!is_instantiated)
		instantiate_handler();
	return i_Type == DEUTERIUM_DOUBLE1;
}

bool PrimitiveTypeHelper::is_integer_derived(DeuteriumPrimitiveType i_Type)
{
	if(!is_instantiated)
		instantiate_handler();
	return i_Type == DEUTERIUM_INT1;
}

bool PrimitiveTypeHelper::is_float_derived(DeuteriumPrimitiveType i_Type)
{
	if(!is_instantiated)
		instantiate_handler();
	return !(is_double_derived(i_Type) || is_integer_derived(i_Type)) && i_Type != DEUTERIUM_UNKNOWN;
}
}