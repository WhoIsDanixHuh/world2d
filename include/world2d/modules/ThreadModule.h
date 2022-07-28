#ifndef WORLD2D_MODULES_THREADMODULE_H
#define WORLD2D_MODULES_THREADMODULE_H

#include "world2d/Module.h"

namespace world2d {
	class ThreadModule : public world2d::Module {
	public:
		ThreadModule();
		ThreadModule(const ThreadModule&) = delete;

		bool Initialize() override;
		const char* GetName() override;
		SDL_ThreadPriority StringToThreadPriority(const char* priorityStr);

		static ThreadModule* Get();
	};
}

#endif