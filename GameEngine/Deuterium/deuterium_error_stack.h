#pragma once
#include <stack>
#define D_ERROR(X) DeuteriumErrorStack::get_instance().push(DeuteriumError(X));
namespace deuterium
{

	class DeuteriumError
	{
	public:
		DeuteriumError(const char* msg) {
			_msg = std::string(msg);
		}
		DeuteriumError(std::string msg) { 
			_msg = msg;
		}
		~DeuteriumError(void) {};
	
		const char* get_message() { return _msg.c_str();}
	private:
		std::string _msg;
	};


	class DeuteriumErrorStack
	{
	public:
		DeuteriumErrorStack();
		~DeuteriumErrorStack();
		static DeuteriumErrorStack& get_instance() { return _stack;}
		bool empty();
		void clear();
		std::string pop();
		void push(DeuteriumError err);
		
	private:
		static DeuteriumErrorStack _stack;
		std::stack<DeuteriumError> _error_stack;
	};

}
