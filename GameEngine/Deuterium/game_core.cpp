#include "game_core.h"
namespace deuterium
{

GameCore::GameCore()
{
	_is_game_core_running = true;
	
}


GameCore::~GameCore()
{
	
}


void GameCore::reset()
{
	//g_data._renderer_ptr->GetDebugCamera().ResetCameraPosition();
}

void GameCore::exit()
{
	this->_is_game_core_running = false;
}

void GameCore::main_loop()
{
	//First process events

	g_data._game_core_ptr->on_event();

	//The Update is called
	g_data._game_core_ptr->update();

	//Finally, render
	g_data._game_core_ptr->render();
}


int GameCore::execute(GameCore* gPtr)
{
	if(!s_game_core)
		s_game_core = gPtr;
	else
		return 1;

	//Javascript tracing
	#ifdef EMSCRIPTEN
	 EM_ASM(
    console.log("Before GameCore::Init()\n");
	);
	#endif

	s_game_core->init();

	//Javascript tracing
	#ifdef EMSCRIPTEN
	 EM_ASM(
    console.log("After GameCore::Init()\n");
	);
	#endif


	//---------------------------------------------------
	//			Native App entry point
	//---------------------------------------------------
#ifdef DEUTERIUM_PC
	while(s_game_core->is_running())
		s_game_core->main_loop();
#endif

	//---------------------------------------------------
	//			Web Browser entry point
	//---------------------------------------------------
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(s_game_core->MainLoop,60,true);
#endif

	return 0;

}

}