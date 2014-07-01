#include "loader.h"

namespace dsm 
{
Loader::Loader(void)
{
}


Loader::~Loader(void)
{
}


const char* Loader::get_error()
{
	if(_error_stack.empty())
		return "";
	else
		return _error_stack.pop();

}
}