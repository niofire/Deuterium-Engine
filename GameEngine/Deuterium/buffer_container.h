#pragma once

#include "global_data.h"

namespace deuterium
{
class BufferContainer
{

public:
					BufferContainer();
	virtual			~BufferContainer();

	virtual void				begin_render() = 0;
	virtual void				end_render() = 0;
	virtual void				reset()		= 0;
	virtual void				delete_buffer() = 0;	
};

}