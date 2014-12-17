#include "game_core.h"
namespace deuterium
{

GameCore::GameCore()
{
	_is_game_core_running = false;
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

}


bool GameCore::execute(GameCore* gPtr)
{
	if(!s_game_core.is_null())
		return false;
	s_game_core.alloc(gPtr);
	
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
	return true;
}

}