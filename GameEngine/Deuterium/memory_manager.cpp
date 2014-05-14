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
	
	if(type != DEUTERIUM_UNKNOWN)
	{
		U8 size_of_type = 0;
		switch(type/10)
	{
		//integers
		case 0:
			size_of_type = sizeof(int);
			break;

		//floats
		case 1:
			size_of_type = sizeof(float);
			break;

		//float matrices
		case 2:
			size_of_type = sizeof(float) * type%10;
			break;

		//doubles
		case 3:
			size_of_type = sizeof(double);
			break;
		default:
			size_of_type = 0;
	};
		return malloc(type %10 * size_of_type);
	}
	return NULL;
	


}