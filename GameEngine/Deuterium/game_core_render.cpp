#include "game_core.h"

namespace deuterium
{

void GameCore::render()
{
	//RENDER
	g_data._renderer_ptr->flush_draw_requests();
		
}
}