#include "render_pipe.h"
#include <vector>
#include <fstream>
#include <string>
#include "uniform_buffer.h"
#include "string_helper.h"
#include "shader_parameter.h"
#include "resource_loader.h"
namespace deuterium
{
	RenderPipe::RenderPipe(void)
	{

	}


	RenderPipe::~RenderPipe(void)
	{

	}

	void RenderPipe::compile(U32 id)
	{
		
	}

	
	void RenderPipe::add_draw_request(dPtr<DrawRequest> req)
	{
		_render_pass_DA[req->_render_pass_id].add_draw_request(req);
	}

	const std::string& RenderPipe::get_render_pass_name(U32 pass_id)
	{
		if(pass_id < _render_pass_DA.size())
		{
			return _render_pass_DA[pass_id].name();
		}
		return "undefined";
	}


}
