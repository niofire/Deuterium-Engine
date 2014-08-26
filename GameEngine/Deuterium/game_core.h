#pragma once

#include "global_data.h"
#include "renderer.h"
#include "mesh_manager.h"
//#include "ShaderParameterAndValueArray_L.h"


//------------------------------------------------------
//			Game Engine Class
//------------------------------------------------------
// Users need to override the Game Engine class in order
// to create their own.
//
namespace deuterium
{

class Texture;

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


protected:
	
	//---------------------------------------------------
	//				static variables
	//---------------------------------------------------
	
	//static pointer to GameEngine instance used
	static dPtr<GameCore> s_game_core;

	//---------------------------------------------------
	//				Member Variable Declaration
	//---------------------------------------------------

	//holds whether the Game core is currently running
	bool		_is_game_core_running;

	//---------------------------------------------------
	//				Test variables
	//---------------------------------------------------
	//ShaderParameterAndValueArray_L m_sValues;
};
}


