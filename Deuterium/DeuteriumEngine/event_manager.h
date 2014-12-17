#pragma once
#include "Renderer.h"

namespace deuterium
{
class EventListener;
class EventManager
{

	enum DeuteriumEvent
	{
		WINDOW_KEYBOARD_INPUT_FOCUS = 0,
		WINDOW_KEYBOARD_INPUT_UNFOCUS,
		KEYBOARD_DOWN,
		KEYBOARD_UP,
		MOUSE_FOCUS,
		MOUSE_UNFOCUS,
		MOUSE_MOVE,
		MOUSE_WHEEL,
		MOUSE_LEFT_BUTTON_UP,
		MOUSE_RIGHT_BUTTON_UP,
		MOUSE_LEFT_BUTTON_DOWN,
		MOUSE_RIGHT_BUTTON_DOWN,
		MOUSE_MIDDLE_BUTTON_UP,
		MOUSE_MIDDLE_BUTTON_DOWN,
		WINDOW_MINIMIZE,
		WINDOW_RESTORE,
		WINDOW_MAXIMIZE,
		WINDOW_RESIZE,
		WINDOW_EXIT,
		UNHANDLED_EVENT,
		NUMBER_OF_EVENTS,
	};

	
public:

	EventManager();
	virtual ~EventManager();

	void UpdateEventManager();
	void Register(EventListener* EventListener, DeuteriumEvent e);
private:
	DeuteriumEvent	SDL_To_Lode(SDL_Event* e);
	std::vector<std::vector<EventListener*> > m_EventListenersDA;

};
}