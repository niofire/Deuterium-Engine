#include "game_core.h"
#include "3rdParty\SDL2\include\SDL.h"
namespace deuterium
{
	dPtr<GameCore> GameCore::s_game_core;

bool GameCore::init()
{

	init_render_context(600,800);
	//Game is now running!
	_is_game_core_running = true;
	
	//Init render context for PC
#ifdef(DEUTERIUM_PC)

#endif
	//Eventmanager Init END
	return true;
}

/*
//Create the gl_context and sets the default back_buffer settings
	init_gl_context(width,height);

	glViewport(0,0,width,height);
	resize_window(width,height);

	this->_debug_camera.set_name("MainCamera");
	/*
	if(!this->load_render_pipe())
	{
		while(!dErrorStack::get_instance().empty())
		{
			std::cout << dErrorStack::get_instance().pop() << std::endl;
		}
	}
	
	//Compile all render pipe assets
	this->_render_pipe.compile_render_pipe();
	*/


void GameCore::init_render_context(const int& width,const int& height)
{
	
	//Init the SDL environment
#ifdef EMSCRIPTEN
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_init Error:" << SDL_GetError() << std::endl;
	}
#elif DEUTERIUM_PC
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_init Error:" << SDL_GetError() << std::endl;
	}
#endif


	//opengl framebuffer settings
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
#elif DEUTERIUM_PC


	if(_sdl_display_window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error:" << SDL_GetError() << std::endl;
	}

	_sdl_opengl_context = SDL_GL_CreateContext(_sdl_display_window);
	
	GLenum err = glewInit();
#endif

}
}