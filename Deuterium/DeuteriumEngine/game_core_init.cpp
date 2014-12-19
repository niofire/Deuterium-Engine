#include "game_core.h"
#include "3rdParty\SDL2\include\SDL.h"
namespace deuterium
{

bool GameCore::init()
{

	//Game is now running!
	_is_game_core_running = true;

	//Set default render context settings create a new 600x800 window
	_render_context.set_default_settings();
	_game_window.create_window(_render_context,600,800);


	//Initalize the renderer
	Renderer::init_renderer();



	//Init render context for PC
#ifdef DEUTERIUM_PC
	
#endif
	//Eventmanager Init END
	return true;
}


}