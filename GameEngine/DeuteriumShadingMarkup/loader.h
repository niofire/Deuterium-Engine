#pragma once
#include "../Deuterium/d_ptr.h"
#include "render_pipe.h"
#include "dsm_error_stack.h"
#include <string>
#include <vector>
namespace dsm
{
	class Loader
	{
	public:
		Loader(void);
		~Loader(void);

		d_ptr<RenderPipe> load_renderpipe(std::string render_pipe_filename, std::string render_assets_package_filename);
	
		const char* get_error();
	private:

		
		DsmErrorStack _error_stack;
	
	};


}
