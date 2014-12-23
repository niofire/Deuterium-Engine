#include "game_core.h"

namespace deuterium
{

	void GameCore::render()
	{
		Renderer::render();
		this->_game_window.swap_buffers();
	}
}