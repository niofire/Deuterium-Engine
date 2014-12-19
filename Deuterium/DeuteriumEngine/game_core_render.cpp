#include "game_core.h"

namespace deuterium
{

	void GameCore::render()
	{
		//Renderer::render();
		glClearColor(0.3f,0.6f,0.1f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		this->_game_window.swap_buffers();
	}
}