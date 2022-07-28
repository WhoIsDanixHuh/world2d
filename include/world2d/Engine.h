#ifndef WORLD2D_ENGINE_H
#define WORLD2D_ENGINE_H

#include "SDL/SDL.h"

#include "world2d/Module.h"
#include <vector>

#define SOL_ALL_SAFETIES_ON 1
#define SOL_SAFE_FUNCTION_CALLS 0

#include <sol/sol.hpp>

#define WORLD2D_VERSION "0.01 WIP"

namespace world2d {
    class Module;

    class Engine {
    private:
        SDL_Window* mSDLWindow = nullptr;
        SDL_Renderer* mSDLRenderer = nullptr;

        SDL_Event mSDLEvent;
        bool mIsRunning = true;

        sol::state mLua;
        std::vector<world2d::Module*> mModules;

        Uint64 mNow, mLast;
        double mDeltaTime;

    public:
        Engine();
        ~Engine();

        void LoadModules();
        bool CompileAndRun(const char* filename);

        SDL_Window* GetSDLWindow();
        SDL_Renderer* GetSDLRenderer();
        sol::state& GetLua();
        double GetDeltaTime();

        static Engine* Get();
    };
}

#endif