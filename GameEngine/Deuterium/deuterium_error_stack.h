#pragma once
#include <stack>
#define D_ERROR(X) DeuteriumErrorStack::get_instance().push(DeuteriumError(X));
namespace deuterium
{

	class DeuteriumError
	{
	public:
		DeuteriumError(const char* msg) { _msg = msg;}
		DeuteriumError(std::string msg) { _msg = msg.c_str();}
		~DeuteriumError(void) {};
	
		const char* get_message() { return _msg;}
	private:
		const char* _msg;
	};


	class DeuteriumErrorStack
	{
	public:
		DeuteriumErrorStack();
		~DeuteriumErrorStack();
		static DeuteriumErrorStack& get_instance() { return _stack;}
		bool empty();
		void clear();
		const char* pop();
		void push(DeuteriumError err);

	private:
		static DeuteriumErrorStack _stack;
		std::stack<DeuteriumError> _error_stack;
	};

}
