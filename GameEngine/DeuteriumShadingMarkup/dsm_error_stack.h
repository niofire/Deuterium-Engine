#pragma once
#include <stack>
namespace dsm
{

	class DsmError
	{
	public:
		DsmError(const char* msg) { _msg = msg;}
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

		bool empty();
		void clear();
		const char* pop();
		void push(DsmError err);

	private:
		std::stack<DsmError> _error_stack;
	};

}
