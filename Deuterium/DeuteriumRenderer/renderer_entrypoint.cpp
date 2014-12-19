#include "renderer.h"

namespace deuterium
{

	//Draw request entry point -
	void Renderer::add_draw_request(U32 render_pass_id, U32 mesh_handle, U32 material_handle, Mat4x4& transform)
	{
		Renderer::get_instance().add_draw_request(DrawRequest(render_pass_id,mesh_handle,material_handle,transform));
	}

	void Renderer::render()
	{
		Renderer::get_instance().flush_draw_requests();
	}

	void Renderer::init_renderer()
	{
		Renderer::get_instance().init();
	}


};