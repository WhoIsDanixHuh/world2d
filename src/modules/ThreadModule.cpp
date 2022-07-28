#include "world2d/lua/structures/Thread.h"
#include "world2d/modules/ThreadModule.h"

#include <cstring>

world2d::ThreadModule::ThreadModule() : world2d::Module() {

}

bool world2d::ThreadModule::Initialize() {
	sol::state& lua = mEngine->GetLua();

	sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
	sol::table luaThreadNamespace { lua.create_table() };

	luaThreadNamespace.new_usertype<world2d::Thread>("Thread",
		sol::constructors<world2d::Thread(sol::function, const char*)>(),

		"name", sol::readonly(&world2d::Thread::name),
		"func", sol::readonly(&world2d::Thread::luaFunc),

		"id", sol::property([&](world2d::Thread& self) {
			return SDL_GetThreadID(self.sdlThread);
		}),

		"Wait", &world2d::Thread::Wait,
		"Deatch", &world2d::Thread::Detach
	);

	luaThreadNamespace.set_function("GetCurrentThreadID", &SDL_ThreadID);
	luaThreadNamespace.set_function("SetCurrentThreadPriority", [&](const char* priorityStr) {
		SDL_ThreadPriority priority = StringToThreadPriority(priorityStr);

		if (SDL_SetThreadPriority(priority) != 0) {
			luaL_error(lua.lua_state(), "Failed to set current thread priority: %s", SDL_GetError());
		}
	});

	luaWorld2dNamespace["Threading"] = luaThreadNamespace;
	return true;
}

const char* world2d::ThreadModule::GetName() {
	return "ThreadModule";
}

SDL_ThreadPriority world2d::ThreadModule::StringToThreadPriority(const char* priorityStr) {
	if (!strcmp(priorityStr, "Low")) return SDL_THREAD_PRIORITY_LOW;
	if (!strcmp(priorityStr, "Normal")) return SDL_THREAD_PRIORITY_NORMAL;
	if (!strcmp(priorityStr, "High")) return SDL_THREAD_PRIORITY_HIGH;
	if (!strcmp(priorityStr, "TimeCritical")) return SDL_THREAD_PRIORITY_TIME_CRITICAL;

	// Let's return low priority as default
	return SDL_THREAD_PRIORITY_LOW;
}

world2d::ThreadModule* world2d::ThreadModule::Get() {
	static world2d::ThreadModule currentModule;
	return &currentModule;
}