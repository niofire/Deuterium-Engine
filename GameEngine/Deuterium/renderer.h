#pragma once

#include <iostream>

#if defined(DEUTERIUM_PC)
#include "3rdParty\SDL2\include\SDL.h"
#include "3rdParty\Glew\include\glew.h"
#endif


#include "global_data.h"
#include "mesh_manager.h"
#include "shader_manager.h"
#include "shader.h"
#include "primitive_type_helper.h"
#include "math.h"
#include "Camera.h"
#include <vector>


#define ADD_DRAWREQUEST(x)	deuterium::g_data._renderer_ptr->add_draw_request(x)

namespace deuterium
{
	
	class ShaderParameterDA;

struct DrawRequest
{
	U32			ShaderId;
	U32			MeshId;
	S32			ZValue;
	bool		IsTransparent;
	ShaderParameterDA* ShaderParamArray;
};

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

	//---------------------------------------------------------
	//					Rendering Function
	//---------------------------------------------------------

	void			add_draw_request(DrawRequest* i_Request);
	void			swap_buffer();
	void			render_draw_request(DrawRequest* i_DrawRequest);
	void			flush_draw_requests();
	//--------------------------------------------------------
	//				Windowing functions
	//--------------------------------------------------------
	void			resize_window(U32 w, U32 h);
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
	Camera			_debug_camera;
	bool			_is_depth_priority;
	std::vector< DrawRequest* >		_draw_request_DA;
};
}