#include "memory_manager.h"

namespace deuterium
{
MemoryManager::MemoryManager(void)
{
}


MemoryManager::~MemoryManager(void)
{
}


void* MemoryManager::alloc_memory(DeuteriumPrimitiveType type,U16 num_values)
{
	int z = PrimitiveTypeHelper::num_of_values(type);
	int d = PrimitiveTypeHelper::size_of(type);
	int x = num_values * PrimitiveTypeHelper::num_of_values(type) * PrimitiveTypeHelper::size_of(type);
	return malloc(num_values * PrimitiveTypeHelper::num_of_values(type) * PrimitiveTypeHelper::size_of(type)); 

	
}


}