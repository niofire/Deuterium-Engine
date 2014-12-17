#pragma once
#include "deuterium.h"

class ClientGameCore : public deuterium::GameCore
{
public:
	ClientGameCore(void);
	~ClientGameCore(void);
	 
	bool init();
	void reset();
	void exit();
	void render();
	void update();
	void on_event();

private:

	

};

