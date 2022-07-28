#ifndef WORLD2D_LUA_STRUCTURES_THREAD_H
#define WORLD2D_LUA_STRUCTURES_THREAD_H

#include "SDL/SDL_thread.h"
#include "sol/sol.hpp"

namespace world2d {
	class Thread {
	public:
		SDL_Thread* sdlThread;
		const char* name;
		sol::function luaFunc;
		
		Thread(sol::function luaFunc, const char* name);

		void Wait();
		void Detach();
	};
}

#endif