#ifndef WORLD2D_MODULES_WINDOWMODULE_H
#define WORLD2D_MODULES_WINDOWMODULE_H

#include "world2d/Engine.h"

namespace world2d {
    class WindowModule : public world2d::Module {
    public:
        WindowModule();
        WindowModule(const WindowModule&) = delete;

        bool Initialize() override;
        void OnEvent(SDL_Event& event) override;
        const char* GetName() override;

        static WindowModule* Get();
    };
}

#endif