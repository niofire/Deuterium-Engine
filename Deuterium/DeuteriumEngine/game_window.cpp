#include "game_window.h"


GameWindow::GameWindow(void)
{
}


GameWindow::~GameWindow(void)
{
}


void GameWindow::create_window()
{
		_handle = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 1,1,
		SDL_WINDOW_OPENGL);
}

void GameWindow::create_window(int w, int h)
{
	create_window();
	resize(w,h);
}

void GameWindow::resize(int w, int h)
{
	SDL_SetWindowSize(_handle,w,h);
}

GameWindow::WindowState GameWindow::get_state()
{

	return _state;
}

void GameWindow::set_state(GameWindow::WindowState state)
{
	switch(state)
	{
	case WindowState::FULLSCREEN:
		SDL_SetWindowFullscreen(_handle,SDL_WINDOW_FULLSCREEN);
		break;

	case WindowState::MINIMIZED:

		break;

	case WindowState::WINDOWED:
		SDL_SetWindowFullscreen(_handle,0);
		break;
	}
	_state = state;
}

void GameWindow::hide()
{

}

void GameWindow::show()
{

}
