#include "renderer.h"

namespace deuterium
{
	void Renderer::flush_draw_requests()
	{
		this->set_clear_color(0.3f,0.6f,0.1f,1.0f);
		this->clear_color_buffer();

		
	
	}

	void Renderer::process_draw_request(dPtr<DrawRequest> i_DrawRequest)
	{
		
	
	}


	void Renderer::set_clear_color(float r, float g, float b,float a)
	{
		glClearColor(r,g,b,a);
	}
}