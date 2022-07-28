#include "world2d/lua/structures/Thread.h"
#include "SDL/SDL_thread.h"

world2d::Thread::Thread(sol::function luaFunc_, const char* name_) : luaFunc(luaFunc_), name(name_) {
	this->sdlThread = SDL_CreateThread([](void* data) {
		static_cast<world2d::Thread*>(data)->luaFunc();
		return 0;
	}, name, this);
}

void world2d::Thread::Wait() {
	SDL_WaitThread(sdlThread, nullptr);
}

void world2d::Thread::Detach() {
	SDL_DetachThread(sdlThread);
}