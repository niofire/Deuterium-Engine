#include "game_core.h"

#pragma comment(lib,	"SDL2/lib/SDL2main.lib")
#pragma comment(lib,	"SDL2/lib/SDL2.lib")
#pragma comment(lib,	"Glew/lib/glew32.lib")
#pragma comment(lib,	"opengl32.lib")

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

}

void GameCore::exit()
{
	this->_is_game_core_running = false;
}

void GameCore::main_loop()
{
	s_core->update();
	s_core->render();
}

dPtr<GameCore> GameCore::s_core;
bool GameCore::execute(GameCore* core)
{	
	if(!s_core.is_null())
		return false;
	s_core.alloc(core);
		//Javascript tracing
	#ifdef EMSCRIPTEN
	 EM_ASM(
    console.log("Before GameCore::Init()\n");
	);
	#endif

	s_core->init();

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
	while (s_core->is_running())
		s_core->main_loop();
#endif

	//---------------------------------------------------
	//			Web Browser entry point
	//---------------------------------------------------
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(s_core->MainLoop,60,true);
#endif
	return true;
}

}


int main(int argc, char* argv[])
{

	return deuterium::GameCore::execute(new deuterium::GameCore());
}