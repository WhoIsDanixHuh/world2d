#include "world2d/Engine.h"

#include "world2d/modules/GraphicsModule.h"
#include "world2d/modules/ImGuiModule.h"

#include "world2d/modules/WindowModule.h"
#include "world2d/modules/KeyboardModule.h"
#include "world2d/modules/JoystickModule.h"
#include "world2d/modules/MouseModule.h"
#include "world2d/modules/AudioModule.h"
#include "world2d/modules/TweeningModule.h"
#include "world2d/modules/ClipboardModule.h"
#include "world2d/modules/ThreadModule.h"
#include "world2d/modules/TimerModule.h"

#include <iostream>
#include <cstring>

int engine_exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description) {
    std::cout << "Error occured: ";

    if (maybe_exception) {
        const std::exception& ex = *maybe_exception;
        std::cout << ex.what();
    } else {
        std::cout.write(description.data(), description.size());
    }

    std::cout << "\n";
    return sol::stack::push(L, description);
}

inline void engine_at_panic(sol::optional<std::string> maybe_msg) {
    if (maybe_msg) {
        const std::string& msg = maybe_msg.value();
        std::cerr << "Lua Error: " << msg << "\n";
    }
}

world2d::Engine::Engine() {

}

world2d::Engine::~Engine() {
    SDL_DestroyRenderer(mSDLRenderer);
    SDL_DestroyWindow(mSDLWindow);

    mSDLRenderer = nullptr;
    mSDLWindow = nullptr;

    SDL_Quit();
}

void world2d::Engine::LoadModules() {
    if (mModules.size() > 0) {
        return;
    }

    mModules.push_back(world2d::GraphicsModule::Get());
    mModules.push_back(world2d::ImGuiModule::Get());

    mModules.push_back(world2d::WindowModule::Get());
    mModules.push_back(world2d::KeyboardModule::Get());
    mModules.push_back(world2d::JoystickModule::Get());
    mModules.push_back(world2d::MouseModule::Get());
    mModules.push_back(world2d::AudioModule::Get());
    mModules.push_back(world2d::TweeningModule::Get());
    mModules.push_back(world2d::ClipboardModule::Get());
    mModules.push_back(world2d::ThreadModule::Get());
    mModules.push_back(world2d::TimerModule::Get());
}

bool world2d::Engine::CompileAndRun(const char* filename) {
    mSDLWindow = SDL_CreateWindow("world2d Application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE);

    if (mSDLWindow == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create SDL window: %s", SDL_GetError());
        return false;
    }

    mSDLRenderer = SDL_CreateRenderer(mSDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (mSDLRenderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create SDL renderer: %s", SDL_GetError());
        return false;
    }

    mLua.open_libraries();

    mLua.set_exception_handler(&engine_exception_handler);
    mLua.set_panic(sol::c_call<decltype(&engine_at_panic), &engine_at_panic>);

    sol::table luaWorld2dNamespace { mLua.create_named_table("world2d") };

    luaWorld2dNamespace["Version"] = WORLD2D_VERSION;
    luaWorld2dNamespace.set_function("GetPlatform", &SDL_GetPlatform);

    for (world2d::Module* module : mModules) {
        if (!module->Initialize()) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize module %s.", module->GetName());
        }
    }

    auto result = mLua.safe_script_file(filename, sol::script_pass_on_error);

    if (!result.valid()) {
        sol::error err = result;
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to compile Lua: %s", err.what());

        return false;
    }

    for (world2d::Module* module : mModules) {
        module->BeforeRun();
    }

    mNow = SDL_GetPerformanceCounter();
    mLast = 0;
    mDeltaTime = 0;

    while (mIsRunning) {
        mLast = mNow;
        mNow = SDL_GetPerformanceCounter();

        mDeltaTime = ((mNow - mLast) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency()));

        while (SDL_PollEvent(&mSDLEvent)) {
            if (mSDLEvent.type == SDL_QUIT) {
                mIsRunning = false;
            }

            for (world2d::Module* module : mModules) {
                module->OnEvent(mSDLEvent);
            }
        }

        for (world2d::Module* module : mModules) {
            module->Update(mDeltaTime);
        }

        SDL_SetRenderDrawColor(mSDLRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mSDLRenderer);

        for (world2d::Module* module : mModules) {
            module->Render();
        }

        SDL_RenderPresent(mSDLRenderer);
    }

    return true;
}

SDL_Window* world2d::Engine::GetSDLWindow() {
    return mSDLWindow;
}

SDL_Renderer* world2d::Engine::GetSDLRenderer() {
    return mSDLRenderer;
}

sol::state& world2d::Engine::GetLua() {
    return mLua;
}

double world2d::Engine::GetDeltaTime() {
    return mDeltaTime;
}

world2d::Engine* world2d::Engine::Get() {
    static world2d::Engine currentEngine;
    return &currentEngine;
}