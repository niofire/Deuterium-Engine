#include "d_error_stack.h"


namespace deuterium
{
	dErrorStack dErrorStack::_stack;

	dErrorStack::dErrorStack()
	{

	}

	dErrorStack::~dErrorStack()
	{

	}

	void dErrorStack::clear()
	{
		while(!_error_stack.empty())
		{
			_error_stack.pop();
		}
	}

	bool dErrorStack::empty()
	{
		return _error_stack.empty();
	}

	std::string dErrorStack::pop()
	{
		std::string msg = _error_stack.top().get_message();
		_error_stack.pop();
		return msg;
	}

	void dErrorStack::push(dError err)
	{
		_error_stack.push(err);
	}
}