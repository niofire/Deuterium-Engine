#pragma once
#include <vector>
#include "d_typedef.h"
namespace deuterium
{

class IMaterial
{
public:
	virtual void bind() = 0;
	virtual void unbind() = 0;
private:
	
	
};
}
