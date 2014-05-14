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
	//gData._renderer_ptr->GetDebugCamera().ResetCameraPosition();
}

void GameCore::exit()
{
	this->_is_game_core_running = false;
}

void GameCore::main_loop()
{
	//First process events
	gData._game_core_ptr->on_event();

	//The Update is called
	gData._game_core_ptr->update();

	//Finally, render
	gData._game_core_ptr->render();
}


int GameCore::execute(GameCore* gPtr)
{
	if(!s_gEngine)
		s_gEngine = gPtr;
	else
		return 1;

	//Javascript tracing
	#ifdef EMSCRIPTEN
	 EM_ASM(
    console.log("Before GameCore::Init()\n");
	);
	#endif

	s_gEngine->init();

	//Javascript tracing
	#ifdef EMSCRIPTEN
	 EM_ASM(
    console.log("After GameCore::Init()\n");
	);
	#endif


	//---------------------------------------------------
	//			Native App entry point
	//---------------------------------------------------
#ifdef _LODEES_PC_
	while(s_gEngine->IsRunning())
		s_gEngine->MainLoop();
#endif

	//---------------------------------------------------
	//			Web Browser entry point
	//---------------------------------------------------
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(s_gEngine->MainLoop,60,true);
#endif

	return 0;

}

}