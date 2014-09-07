#pragma once
#include <stack>
#define D_ERROR(X) dErrorStack::get_instance().push(dError(X));
namespace deuterium
{

	class dError
	{
	public:
		dError(const char* msg) {
			_msg = std::string(msg);
		}
		dError(std::string msg) { 
			_msg = msg;
		}
		~dError(void) {};
	
		const char* get_message() { return _msg.c_str();}
	private:
		std::string _msg;
	};


	class dErrorStack
	{
	public:
		dErrorStack();
		~dErrorStack();
		static dErrorStack& get_instance() { return _stack;}
		bool empty();
		void clear();
		std::string pop();
		void push(dError err);
		void push(const std::string& err_msg) { this->push(dError(err_msg));}
	private:
		static dErrorStack _stack;
		std::stack<dError> _error_stack;
	};

}
