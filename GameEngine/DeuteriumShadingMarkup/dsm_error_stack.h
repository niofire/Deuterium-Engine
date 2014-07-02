#pragma once
#include <stack>
namespace dsm
{

	class DsmError
	{
	public:
		DsmError(const char* msg) { _msg = msg;}
		DsmError(std::string msg) { _msg = msg.c_str();}
		~DsmError(void);
	
		const char* get_message() { return _msg;}
	private:
		const char* _msg;
	};


	class DsmErrorStack
	{
	public:
		DsmErrorStack();
		~DsmErrorStack();
		static DsmErrorStack& get_instance() { return _stack;}
		bool empty();
		void clear();
		const char* pop();
		void push(DsmError err);

	private:
		static DsmErrorStack _stack;
		std::stack<DsmError> _error_stack;
	};

}
