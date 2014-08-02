#include <iostream>
#include "client_game_core.h"

//---------------------------
//			TEST
//---------------------------
#include "resource_loader.h"

int main(int argc, char* argv[])
{

	using namespace deuterium;
	ResourceLoader loader;
	loader.load_render_assets("C:\\Users\\Mathieu\\Documents\\GitHub\\Deuterium\\GameEngine\\Deuterium\\Resources\\Rendering_assets\\default.render_assets_package");
	return 0;

	//return ClientGameCore::execute(new ClientGameCore());
}