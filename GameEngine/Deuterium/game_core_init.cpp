#include "game_core.h"
#include "texture.h"
#include "event_listener.h"
#include "event_manager.h"

namespace deuterium
{
dPtr<GameCore> GameCore::s_game_core;
GlobalData g_data;

bool GameCore::init()
{

	//Check if init has already been called.
	if(!g_data._game_core_ptr.is_null())
		return false;

	//Game is now running!
	_is_game_core_running = true;
	

	// GameCore Init START
	g_data._game_core_ptr = dPtr<GameCore>(this);
	//GameCore Init END

	//Renderer Init START
	g_data._renderer_ptr = dPtr<Renderer>(new Renderer());
	g_data._renderer_ptr->init(500,500);
	//Renderer Init END
	

	//MeshManager Init START
	g_data._mesh_manager_ptr = dPtr<MeshManager>(new MeshManager());
	
	//ShaderManager Init START
	//g_data._shader_manager_ptr = new ShaderManager();
	//ShaderManager Init END

	//EventManager Init START
	g_data._event_manager_ptr = dPtr<EventManager>(new EventManager());
	//Eventmanager Init END
	return true;
}
}