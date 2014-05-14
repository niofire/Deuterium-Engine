

#if defined(DEUTERIUM_PC)
#include "renderer.h"
#pragma comment(lib, "3rdParty/SDL2/lib/SDL2main.lib")
#pragma comment(lib, "3rdParty/SDL2/lib/SDL2.lib")
#pragma comment(lib, "3rdParty/Glew/lib/glew32.lib")
#pragma comment(lib, "opengl32.lib")
#endif

namespace deuterium
{
Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}




void Renderer::clear_color_buffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::clear_depth_buffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::clear_color_and_depth_buffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


Mat4x4 Renderer::perspective_projection_matrix(float left, float right, float bottom, float top, float near, float far)
{
	//Load matrix
	Mat4x4 cameraToClipMatrix;
	for(int i = 0; i < 4; ++i)
		cameraToClipMatrix[i][i] = 0.0f;
	cameraToClipMatrix[0].x = right;
	cameraToClipMatrix[1].y = top;
	cameraToClipMatrix[2].x = (right + left) / (right - left);
	cameraToClipMatrix[2].y = (top + bottom)/ (top - bottom);
	cameraToClipMatrix[2].z = -(far + near) / (far - near);
	cameraToClipMatrix[2].w = -1.0f;
	cameraToClipMatrix[3].z = (-2*far*near)/(far-near);

	//return m4 uniform
	return cameraToClipMatrix;
}



Mat4x4 Renderer::perspective_projection_matrix(float FOV, float AspectRatio, float zNear, float zFar)
{
	//Convert FOV to screen size
	float degToRad = 3.141589f * 2.0f / 360.0f;
	float FovRad = FOV * degToRad;
	float size = 1.0f/tan(FovRad);

	//Call Perspective Matrix func
	return perspective_projection_matrix(-size,size,-size,size * AspectRatio,zNear,zFar);
}


void Renderer::resize_window(U32 w, U32 h)
{
#if defined DEUTERIUM_PC
	SDL_SetWindowSize(this->_sdl_display_window,w,h);
#endif
}


void Renderer::add_draw_request(DrawRequest* request)
{
	_draw_request_DA.push_back(request);
}
}