#pragma once

#if defined(DEUTERIUM_PC)
#include "3rdParty\SDL2\include\SDL.h"
#include "3rdParty\Glew\include\glew.h"
#endif

#include "draw_request.h"
#include "d_typedef.h"
#include "d_ptr.h"
#include <vector>



namespace deuterium
{
class Renderer
{
public:
	//---------------------------------------------------------
	//					Constructor / Destructor
	//---------------------------------------------------------
	virtual			~Renderer();


	//---------------------------------------------------------
	//					Core functions
	//---------------------------------------------------------
	void			update();
	void			init();

	//---------------------------------------------------------
	//					Render Settings
	//---------------------------------------------------------



	//---------------------------------------------------------
	//					Rendering Function
	//---------------------------------------------------------

	void			add_draw_request(DrawRequest request);
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

public:
	//------------------------------------------------------
	//				Dll Entry Points
	//------------------------------------------------------
	static __declspec(dllexport) void add_draw_request(U32 render_pass_id, U32 mesh_handle, U32 material_handle, Mat4x4& transform);   
   
    static __declspec(dllexport) void render();   
   
    static __declspec(dllexport) void init_renderer();   
   

	static Renderer& get_instance();
private:
	
	Renderer();
	static dPtr<Renderer> s_renderer;
	
	
	bool			_is_depth_priority;
	std::vector<DrawRequest> _draw_request_DA;
};
}