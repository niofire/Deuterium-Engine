#pragma once

#include "global_data.h"
#include <string>
namespace deuterium
{
class PrimitiveTypeHelper
	{

	public:
		struct TypeData
		{
			U32			_num_values;
			U32			_size_of_primitive;
			DeuteriumPrimitiveType	_type;
		};
	public:
		PrimitiveTypeHelper();
		~PrimitiveTypeHelper();
		static U32		num_of_values(DeuteriumPrimitiveType type);

		static bool	is_float_derived(DeuteriumPrimitiveType type);
		static bool	is_integer_derived(DeuteriumPrimitiveType type);
		static bool	is_double_derived(DeuteriumPrimitiveType type);
		static DeuteriumPrimitiveType parse_string_for_type(std::string i_String);
	private:
		static void	 instantiate_handler();
		static	bool	is_instantiated;
		static TypeData _type_info[DEUTERIUM_UNKNOWN];

	};
}