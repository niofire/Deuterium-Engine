#pragma once
#include "global_data.h"
#include <stdlib.h>
#include "primitive_type_helper.h"
namespace deuterium
{
class MemoryManager
{
public:
	MemoryManager(void);
	~MemoryManager(void);
	
	static void* alloc_memory(DeuteriumPrimitiveType type, U16 num_values);

};

}