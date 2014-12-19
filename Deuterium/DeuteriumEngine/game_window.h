#pragma once
#include "3rdParty\SDL2\include\SDL.h"
#include "render_context.h"
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

	
	void create_window(RenderContext& c);
	void create_window(RenderContext& c, int w, int h);

	//---------------------------------------
	//			Window Parameters
	//---------------------------------------
	void set_name(const char* name);

	//---------------------------------------
	//			Window Handling functions
	//---------------------------------------
	void resize(int w, int h);
	void hide();
	void show();

	//---------------------------------------
	//			Window State functions
	//---------------------------------------
	void set_state(WindowState state);
	WindowState get_state() {return _state; }
	bool is_valid() const { return _handle != nullptr; }

	//---------------------------------------
	//			Rendering functions
	//---------------------------------------
	void swap_buffers();

private:
	const char* _name;
	WindowState _state;
	SDL_Window* _handle;


};

