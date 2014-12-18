#include "game_core.h"

#pragma comment(lib,	"SDL2/lib/x86/SDL2main.lib")
#pragma comment(lib,	"SDL2/lib/x86/SDL2.lib")
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
	//g_data._renderer_ptr->GetDebugCamera().ResetCameraPosition();
}

void GameCore::exit()
{
	this->_is_game_core_running = false;
}

void GameCore::main_loop()
{

}


bool GameCore::execute(GameCore* core)
{	
	//Javascript tracing
	#ifdef EMSCRIPTEN
	 EM_ASM(
    console.log("Before GameCore::Init()\n");
	);
	#endif

	core->init();

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
	while (core->is_running())
		core->main_loop();
#endif

	//---------------------------------------------------
	//			Web Browser entry point
	//---------------------------------------------------
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(core->MainLoop,60,true);
#endif
	return true;
}

}

int main(int argc, char* argv[])
{
	return deuterium::GameCore::execute(new deuterium::GameCore());
}