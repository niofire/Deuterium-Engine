#include "deuterium_error_stack.h"


namespace deuterium
{
	DeuteriumErrorStack DeuteriumErrorStack::_stack;

	DeuteriumErrorStack::DeuteriumErrorStack()
	{

	}

	DeuteriumErrorStack::~DeuteriumErrorStack()
	{

	}

	void DeuteriumErrorStack::clear()
	{
		while(!_error_stack.empty())
		{
			_error_stack.pop();
		}
	}

	bool DeuteriumErrorStack::empty()
	{
		return _error_stack.empty();
	}

	std::string DeuteriumErrorStack::pop()
	{
		std::string msg = _error_stack.top().get_message();
		_error_stack.pop();
		return msg;
	}

	void DeuteriumErrorStack::push(DeuteriumError err)
	{
		_error_stack.push(err);
	}
}