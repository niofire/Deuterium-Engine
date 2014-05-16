#include "game_core.h"
#include "event_manager.h"

namespace deuterium
{

	void GameCore::on_event()
{
	g_data._event_manager_ptr->UpdateEventManager();
}
}

