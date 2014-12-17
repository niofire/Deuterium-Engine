#include "renderer.h"

namespace deuterium
{
	void Renderer::flush_draw_requests()
	{
	//Swap the buffers
	this->swap_buffer();


	
	}
	void Renderer::render_draw_request(DrawRequest* i_DrawRequest)
	{
		/*
		Mesh*		l_Mesh		= g_data._mesh_manager_ptr->mesh_by_id(i_DrawRequest->MeshId);

		VertexBufferContainer*		l_Vbo	= l_Mesh->vertex_buffer_ptr();
		IndexBufferContainer*		l_Ibo	= l_Mesh->index_buffer_ptr();

	


		//Update Shader Param


			//s_param_DA.clean_parameters(l_Shader.shader_handle());
			//l_Shader.bind_current_parameters();
	
	
		//l_Shader.begin_render();

	
		l_Vbo->begin_render();
		l_Ibo->begin_render();

		glDrawElements(GL_TRIANGLES,l_Ibo->num_elements(),GL_UNSIGNED_SHORT,0);

		l_Vbo->end_render();
		l_Ibo->end_render();
	
		//l_Shader.end_render();
		*/
	
	}

	void Renderer::swap_buffer()
	{

	#ifdef EMSCRIPTEN
		SDL_GL_SwapBuffers();
	#elif DEUTERIUM_PC
		SDL_GL_SwapWindow(_sdl_display_window);
	#endif

	}


	void Renderer::set_clear_color(float r, float g, float b,float a)
	{
		glClearColor(r,g,b,a);
	}
}