#include "renderer.h"

namespace deuterium
{
	void Renderer::flush_draw_requests()
{

	//Setting up some default render states
	this->set_clear_color(1,0,1,1);
	this->clear_color_and_depth_buffer();
	glEnable(GL_DEPTH_TEST);
	

	//---------------------------------------------------
	//	Draw Call sorting

	//The currently rendering shader
	U32 l_CurrentRenderingShaderId = 0;

	DrawRequest *l_DrawRequestTemp;

	U32 l_CurrentIndex = 0;

	while(l_CurrentIndex < _draw_request_DA.size())
	{
		l_CurrentRenderingShaderId = _draw_request_DA[l_CurrentIndex]->ShaderId;
		for(U32 j = l_CurrentIndex + 1; j<_draw_request_DA.size(); ++j)
		{
			if(_draw_request_DA[l_CurrentIndex]->ShaderId == _draw_request_DA[j]->ShaderId)
			{
				if(l_CurrentIndex == j - 1)
					l_CurrentIndex++;
				else
				{
					l_DrawRequestTemp = _draw_request_DA[j];
					_draw_request_DA[j] = _draw_request_DA[l_CurrentIndex + 1];
					_draw_request_DA[l_CurrentIndex + 1] = l_DrawRequestTemp;
					l_CurrentIndex++;
				}
			}
		}
		l_CurrentIndex++;
	}
	U32 l_CurrentShaderId = 0;
	/*for(U32 i =0 ;i < _draw_request_DA.size();++i)
	{
		//Change Shader
		if(_draw_request_DA[i]->ShaderId != l_CurrentShaderId)
		{
			if(l_CurrentShaderId != 0)
				g_data._shader_manager_ptr->GetShader(l_CurrentShaderId).end_render();
			
			l_CurrentShaderId = _draw_request_DA[i]->ShaderId;
			g_data._shader_manager_ptr->GetShader(l_CurrentShaderId).begin_render();
		}

		//Process draw request
		render_draw_request(_draw_request_DA[i]);
	}
	
	//End render on last shader used
	Shader l_lastShader = g_data._shader_manager_ptr->GetShader(l_CurrentShaderId);
	
	
	l_lastShader.end_render();
	*/
	//Swap the buffers
	this->swap_buffer();

	//Free the DrawRequest memory
	for(U32 i = 0; i < _draw_request_DA.size();++i)
	{
		delete _draw_request_DA[i];
		_draw_request_DA[i] = NULL;
	}
	
	//Clear the drawRequest structure
	_draw_request_DA.clear();
	
}
void Renderer::render_draw_request(DrawRequest* i_DrawRequest)
{
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
	
	
}

void Renderer::swap_buffer()
{

#ifdef EMSCRIPTEN
	//SDL_GL_SwapBuffers();
#else
	SDL_GL_SwapWindow(_sdl_display_window);
#endif

}


void Renderer::set_clear_color(float r, float g, float b,float a)
{
	glClearColor(r,g,b,a);
}
}