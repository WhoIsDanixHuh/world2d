#ifndef WORLD2D_MODULES_THREADMODULE_H
#define WORLD2D_MODULES_THREADMODULE_H

#include "world2d/Module.h"

namespace world2d {
	struct Thread {
		SDL_Thread* sdlThread;
		const char* name;
		sol::function luaFunc;

		Thread(sol::function luaFunc, const char* threadName);
	};

	class ThreadModule : public world2d::Module {
	public:
		ThreadModule();
		ThreadModule(const ThreadModule&) = delete;

		bool Initialize();
		SDL_ThreadPriority StringToThreadPriority(const char* priorityStr);

		static ThreadModule* Get();
	};
}

#endif