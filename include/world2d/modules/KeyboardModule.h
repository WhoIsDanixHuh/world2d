#ifndef WORLD2D_MODULES_KEYBOARDMODULE_H
#define WORLD2D_MODULES_KEYBOARDMODULE_H

#include "world2d/Module.h"

namespace world2d {
    class KeyboardModule : public world2d::Module {
    public:
        const char* name = "KeyboardModule";

        KeyboardModule();
        KeyboardModule(const KeyboardModule&) = delete;

        bool Initialize() override;
        void OnEvent(SDL_Event& event) override;
        const char* GetName();

        static KeyboardModule* Get();
    };
}

#endif