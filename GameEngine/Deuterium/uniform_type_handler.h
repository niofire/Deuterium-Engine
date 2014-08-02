#pragma once
#include "global_data.h"
#include "string_helper.h"
namespace deuterium
{
	enum DeuteriumUniformType
	{
		D_INT,
		D_UINT,
		D_FLOAT,
		D_VEC2,
		D_VEC3,
		D_VEC4,
		D_IVEC2,
		D_IVEC3,
		D_IVEC4,
		D_UIVEC2,
		D_UIVEC3,
		D_UIVEC4,
		D_MAT2,
		D_MAT3,
		D_MAT4,
		D_UNKNOWN_UNIFORM_TYPE
	};
	
	//update this if ever a uniform type is added
	#define NUMBER_OF_DEUTERIUM_UNIFORM_TYPE 15
	class UniformTypeHandler
	{
	public:
		struct UniformTypeData
		{
			UniformTypeData(std::string name, U32 num_values, U32 byte_size, DeuteriumUniformType type)
			{
				_name = name;
				_num_values = num_values;
				_byte_size = byte_size;
				_type = type;
			}
			std::string _name;
			U32			_num_values;
			U32			_byte_size;
			DeuteriumUniformType	_type;
		};



	public:

		static void_d_ptr alloc_memory(DeuteriumUniformType type,const U32& num);
		static std::string to_string(DeuteriumUniformType type);
		static DeuteriumUniformType to_enum(const std::string& str);
		static const U32&		num_of_values(DeuteriumUniformType type);
		static const U32&		size_of(DeuteriumUniformType type);
		static bool	is_float_derived(DeuteriumUniformType type);
		static bool	is_integer_derived(DeuteriumUniformType type);
		static U32 num_of_uniform_types() {return NUMBER_OF_DEUTERIUM_UNIFORM_TYPE;}
	private:
		UniformTypeHandler();
		~UniformTypeHandler();
		static UniformTypeData _uniform_type_data_array[NUMBER_OF_DEUTERIUM_UNIFORM_TYPE];		
	};



}
