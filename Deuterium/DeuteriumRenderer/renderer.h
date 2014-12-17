#pragma once

#include <iostream>

#if defined(DEUTERIUM_PC)
#include "3rdParty\SDL2\include\SDL.h"
#include "3rdParty\Glew\include\glew.h"
#endif

#include "mesh_manager.h"

#include "math.h"
#include <vector>
#include "render_pipe.h"
#include "d_typedef.h"

#include "draw_request.h"


//#define ADD_DRAWREQUEST(draw_request)	deuterium::g_data._renderer_ptr->add_draw_request(draw_request)/////...
//#define ADD_RENDER_PASS_TYPE(enum_name, render_pass_name) 
namespace deuterium
{




class Renderer
{
public:
	//---------------------------------------------------------
	//					Constructor / Destructor
	//---------------------------------------------------------
	virtual			~Renderer();
					Renderer();

	//---------------------------------------------------------
	//					Core functions
	//---------------------------------------------------------
	void			update(float i_fDeltaTime);
	void			init();
	void			init_render_context(int w, int h);

	//---------------------------------------------------------
	//					Render Settings
	//---------------------------------------------------------



	//---------------------------------------------------------
	//					Rendering Function
	//---------------------------------------------------------

	void			add_draw_request(dPtr<DrawRequest> request);
	void			swap_buffer();
	void			flush_draw_requests();
	void			process_draw_request(dPtr<DrawRequest> request);
	//--------------------------------------------------------
	//				Helper Function
	//--------------------------------------------------------
	Mat4x4			perspective_projection_matrix(float left, float right, float bottom, float top, float near, float far);
	Mat4x4			perspective_projection_matrix(float FOV, float AspectRatio, float zNear, float zFar);

	//-------------------------------------------------------
	//				RenderState functions
	//-------------------------------------------------------
	void			clear_color_buffer();
	void			clear_depth_buffer();
	void			clear_color_and_depth_buffer();
	void			set_clear_color(float r,float g,float b,float a);
	void			set_depth_priority(bool val)	{_is_depth_priority = val;}

private:
#if defined DEUTERIUM_PC
	SDL_Window*		_sdl_display_window;
	SDL_GLContext	_sdl_opengl_context;
#elif defined EMSCRIPTEN
	SDL_Surface * l_DisplayScreen = NULL;
#endif
	bool			_is_depth_priority;
	std::vector<dPtr<DrawRequest> > _draw_request_DA;
};
}