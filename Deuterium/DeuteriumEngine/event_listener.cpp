#include "event_listener.h"

namespace deuterium
{

EventListener::EventListener()
{

}

EventListener::~EventListener()
{

}

void EventListener::OnEvent(SDL_Event* Event) {

}

void EventListener::OnInputFocus() {
	//Pure virtual, do nothing
}

void EventListener::OnInputBlur() {
	//Pure virtual, do nothing
}

void EventListener::OnKeyDown(const Uint8* k_ptr) {
	//Pure virtual, do nothing
}

void EventListener::OnKeyUp(const Uint8* k_ptr) {
	//Pure virtual, do nothing
}

void EventListener::OnMouseFocus() {
	//Pure virtual, do nothing
}

void EventListener::OnMouseBlur() {
	//Pure virtual, do nothing
}

void EventListener::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
	//Pure virtual, do nothing
}

void EventListener::OnMouseWheel(bool Up, bool Down) {
	//Pure virtual, do nothing
}

void EventListener::OnLButtonDown(int mX, int mY) {
	//Pure virtual, do nothing
}

void EventListener::OnLButtonUp(int mX, int mY) {
	//Pure virtual, do nothing
}

void EventListener::OnRButtonDown(int mX, int mY) {
	//Pure virtual, do nothing
}

void EventListener::OnRButtonUp(int mX, int mY) {
	//Pure virtual, do nothing
}

void EventListener::OnMButtonDown(int mX, int mY) {
	//Pure virtual, do nothing
}

void EventListener::OnMButtonUp(int mX, int mY) {
	//Pure virtual, do nothing
}

void EventListener::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {
	//Pure virtual, do nothing
}

void EventListener::OnJoyButtonDown(Uint8 which,Uint8 button) {
	//Pure virtual, do nothing
}

void EventListener::OnJoyButtonUp(Uint8 which,Uint8 button) {
	//Pure virtual, do nothing
}

void EventListener::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) {
	//Pure virtual, do nothing
}

void EventListener::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {
	//Pure virtual, do nothing
}

void EventListener::OnMinimize() {
	//Pure virtual, do nothing
}

void EventListener::OnRestore() {
	//Pure virtual, do nothing
}

void EventListener::OnResize(int w,int h) {
	//Pure virtual, do nothing
}

void EventListener::OnExpose() {
	//Pure virtual, do nothing
}

void EventListener::OnExit() {
	//Pure virtual, do nothing
}

void EventListener::OnUser(Uint8 type, int code, void* data1, void* data2) {
	//Pure virtual, do nothing
}
}