#include "game_window.h"


GameWindow::GameWindow(void)
{
	_state = WINDOWED;
	_name = "";
}


GameWindow::~GameWindow(void)
{
}


void GameWindow::create_window(RenderContext& context)
{
	context.setup_context();
	
	#ifdef EMSCRIPTEN
	l_DisplayScreen = SDL_SetVideoMode(
		width, height, 32,
		SDL_ANYFORMAT | SDL_OPENGL);
	#elif DEUTERIUM_PC
	_handle = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1, 1,
		SDL_WINDOW_OPENGL);
	if (_handle == nullptr)
	{
		std::cout << "SDL_CreateWindow Error:" << SDL_GetError() << std::endl;
	}
	#endif
	context.create_context(_handle);
	this->_render_context = context;

	GLenum err = glewInit();
}

void GameWindow::create_window(RenderContext& c, int w, int h)
{
	create_window(c);
	resize(w,h);
}

void GameWindow::resize(int w, int h)
{
	SDL_SetWindowSize(_handle,w,h);
}

void GameWindow::set_state(GameWindow::WindowState state)
{
	switch(state)
	{
	case WindowState::FULLSCREEN:
		SDL_SetWindowFullscreen(_handle,SDL_WINDOW_FULLSCREEN);
		break;

	case WindowState::MINIMIZED:
		SDL_MinimizeWindow(_handle);
		break;

	case WindowState::WINDOWED:
		SDL_RestoreWindow(_handle);
		SDL_SetWindowFullscreen(_handle,0);
		break;
	}
	_state = state;
}



void GameWindow::hide()
{
	SDL_HideWindow(_handle);
}

void GameWindow::show()
{
	SDL_ShowWindow(_handle);
}

void GameWindow::swap_buffers()
{
	SDL_GL_SwapWindow(_handle);
}
