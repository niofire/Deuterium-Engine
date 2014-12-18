#include "render_context.h"


RenderContext::RenderContext(void)
{
	set_default_settings();
}


RenderContext::~RenderContext(void)
{
}

void RenderContext::set_default_settings()
{
	_settings.red	= 8;
	_settings.green	= 8;
	_settings.blue	= 8;
	_settings.alpha	= 8;

	_settings.depth		= 8;
	_settings.stencil	= 8;

	_settings.numberOfBuffers	= 2;

}

void RenderContext::bind_context_attributes()
{
	//opengl framebuffer settings
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, _settings.red);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, _settings.green);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, _settings.blue);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, _settings.alpha);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
}

void RenderContext::init_SDL()
{
	//Init the SDL environment
#ifdef EMSCRIPTEN
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_init Error:" << SDL_GetError() << std::endl;
	}
#elif DEUTERIUM_PC
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_init Error:" << SDL_GetError() << std::endl;
	}
#endif
}
void RenderContext::setup_context()
{
	init_SDL();

	bind_context_attributes();
}

void RenderContext::create_context(SDL_Window* window)
{
	_context = SDL_GL_CreateContext(window);	
}


void RenderContext::destroy_context()
{
	SDL_GL_DeleteContext(_context);
}

void RenderContext::set_depth_buffer_size(U8 depth, U8 stencil)
{
	_settings.depth = depth;
	_settings.stencil = stencil;
}

void RenderContext::set_frame_buffer_size(U8 r, U8 g, U8 b, U8 a)
{
	_settings.red = r;
	_settings.green = g;
	_settings.blue = b;
	_settings.alpha  =a;
}
