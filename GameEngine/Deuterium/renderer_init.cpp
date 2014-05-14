#include "renderer.h"
namespace deuterium
{
void Renderer::init(int width, int height)
{
	init_gl_context(width,height);

	glViewport(0,0,width,height);
	resize_window(width,height);

	this->_debug_camera.set_name("MainCamera");
	
}


void Renderer::init_gl_context(int width, int height)
{
		
#ifdef EMSCRIPTEN
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_init Error:" << SDL_GetError() << std::endl;
	}
#else
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_init Error:" << SDL_GetError() << std::endl;
	}
#endif
	//open_gl settings, usually default, just for template
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,        32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

#ifdef EMSCRIPTEN
	l_DisplayScreen = SDL_SetVideoMode(
		width, height, 32,
		  SDL_ANYFORMAT | SDL_OPENGL);
#else
	_sdl_display_window = SDL_CreateWindow("SDL2 OpenglExample", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 1,1,
		SDL_WINDOW_OPENGL);

	if(_sdl_display_window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error:" << SDL_GetError() << std::endl;
	}
	_sdl_opengl_context = SDL_GL_CreateContext(_sdl_display_window);
	


	GLenum err = glewInit();
#endif
}
}