#pragma once

#include <iostream>

#if defined(DEUTERIUM_PC)
#include "3rdParty\SDL2\include\SDL.h"
#include "3rdParty\Glew\include\glew.h"
#endif


#include "global_data.h"
#include "mesh_manager.h"

#include "math.h"
#include "Camera.h"
#include <vector>
#include "render_pipe.h"

#include "scene_object.h"



#define ADD_DRAWREQUEST(draw_request)	deuterium::g_data._renderer_ptr->add_draw_request(draw_request)
#define ADD_RENDER_PASS_TYPE(enum_name, render_pass_name) 
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
	void			init(int width, int height);
	void			init_gl_context(int w, int h);
	bool			load_render_pipe();
	//---------------------------------------------------------
	//					Rendering Function
	//---------------------------------------------------------

	void			add_draw_request(DrawRequest* i_Request);
	void			swap_buffer();
	void			render_draw_request(DrawRequest* i_DrawRequest);
	void			flush_draw_requests();
	U32				get_render_pass_id(const std::string& pass_name);
	const std::string& get_render_pass_name(U32 id);
	//--------------------------------------------------------
	//				Windowing functions
	//--------------------------------------------------------
	void			resize_window(U32 w, U32 h);
	const Vec2f&	window_size() { return this->_window_size;}
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


	static const char* s_render_settings_config_filepath;
	//-------------------------------------------------------
	//				Debug Camera
	//--------------------------------------------------------
	Camera&		debug_camera()	{return _debug_camera;}

private:
#if defined DEUTERIUM_PC
	SDL_Window*		_sdl_display_window;
	SDL_GLContext	_sdl_opengl_context;
#elif defined EMSCRIPTEN
	SDL_Surface * l_DisplayScreen = NULL;
#endif
	Vec2f _window_size;
	Camera			_debug_camera;
	bool			_is_depth_priority;
	std::vector< DrawRequest* >		_draw_request_DA;
	RenderPipe _render_pipe;
};
}