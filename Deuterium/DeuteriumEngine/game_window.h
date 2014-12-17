#pragma once
#include "3rdParty\SDL2\include\SDL.h"
class GameWindow
{
public:
	enum WindowState
	{
		MINIMIZED,
		FULLSCREEN,
		WINDOWED
	};

public:
	GameWindow(void);
	~GameWindow(void);

	
	void create_window();
	void create_window(int w, int h);

	//---------------------------------------
	//			Window Parameters
	//---------------------------------------
	void set_name(const char* name);

	//---------------------------------------
	//			Window Handling function
	//---------------------------------------
	void resize(int w, int h);
	void hide();
	void show();
	void set_state(WindowState state);
	WindowState get_state() {return _state; }

private:
	const char* _name;
	WindowState _state;
	SDL_Window* _handle;


};

