#include <iostream>
#include "client_game_core.h"


int main(int argc, char* argv[])
{

	using namespace deuterium;

	return ClientGameCore::execute(new ClientGameCore());
}