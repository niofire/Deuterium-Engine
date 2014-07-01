#include "dsm_error_stack.h"


namespace dsm
{
	DsmErrorStack::DsmErrorStack()
	{

	}

	DsmErrorStack::~DsmErrorStack()
	{

	}

	void DsmErrorStack::clear()
	{
		while(!_error_stack.empty())
		{
			_error_stack.pop();
		}
	}

	bool DsmErrorStack::empty()
	{
		return _error_stack.empty();
	}

	const char* DsmErrorStack::pop()
	{
		const char* msg = _error_stack.top().get_message();
		_error_stack.pop();
		return msg;
	}

	void DsmErrorStack::push(DsmError err)
	{
		_error_stack.push(err);
	}
}