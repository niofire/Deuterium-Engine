#pragma once
#include "d_ptr.h"
#include "global_data.h"
#include "render_context.h"
#include "game_window.h"
#include "renderer.h"
//------------------------------------------------------
//			Game Engine Class
//------------------------------------------------------
// Users need to override the Game Engine class in order
// to create their own.
//
namespace deuterium
{
class GameCore
{
public:
	GameCore();
	virtual ~GameCore();

	//---------------------------------------------------
	//				Game Loop
	//---------------------------------------------------
	static bool execute(GameCore*);
	static void main_loop();

	//--------------------------------------------------
	//				Virtual core function - To override in Users Main Engine
	//--------------------------------------------------
	//  These functions can be overriden by your own GameEngine class
	virtual bool init();
	virtual void reset();
	virtual void exit();
	virtual void render();
	virtual void update();
	virtual void on_event();

	//---------------------------------------------------
	//				core status function
	//---------------------------------------------------
	inline	bool	is_running() const {return _is_game_core_running;}
	
	//---------------------------------------------------
	//				Render Environment
	//---------------------------------------------------
	bool			init_render_content(int w, int h);
protected:
	
	GameWindow _game_window;
	RenderContext _render_context;


	//holds whether the Game core is currently running
	bool		_is_game_core_running;
	

private:
	static dPtr<GameCore> s_core;
};
}


