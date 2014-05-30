#pragma once
#include "deuterium_error.h"
namespace deuterium
{
class DeuteriumErrorManager
{
public:


	static DeuteriumErrorManager& get_instance() { return _e_manager;}
	

	void push_error_on_stack(DeuteriumError error);
	void clear_stack();
	void display_stack();
	void display_and_clear_stack();

private:
	static DeuteriumErrorManager _e_manager;
	DeuteriumErrorManager();
	~DeuteriumErrorManager();
};

}