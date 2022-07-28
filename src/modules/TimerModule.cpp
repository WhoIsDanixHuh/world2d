#include "world2d/modules/TimerModule.h"

world2d::TimerModule::TimerModule() : world2d::Module() {

}

bool world2d::TimerModule::Initialize() {
    if (SDL_Init(SDL_INIT_TIMER) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL timer subsystem: %s", SDL_GetError());
        return false;
    }

    sol::state& lua = mEngine->GetLua();

    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
    sol::table luaTimerNamespace { lua.create_table() };

    // ===== Functions =====
    luaTimerNamespace.set_function("Delay", &SDL_Delay);

    luaTimerNamespace.set_function("GetFPS", [&]() {
        return 1000 / world2d::Engine::Get()->GetDeltaTime();
    });
    // =====================

    luaWorld2dNamespace["Timer"] = luaTimerNamespace;
    return true;
}

const char* world2d::TimerModule::GetName() {
    return "TimerModule";
}

world2d::TimerModule* world2d::TimerModule::Get() {
    static world2d::TimerModule currentModule;
    return &currentModule;
}