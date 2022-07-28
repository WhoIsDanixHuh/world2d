#ifndef WORLD2D_MODULES_MOUSEMODULE_H
#define WORLD2D_MODULES_MOUSEMODULE_H

#include "world2d/Module.h"

namespace world2d {
    class MouseModule : public world2d::Module {
    public:
        MouseModule();
        MouseModule(const MouseModule&) = delete;

        bool Initialize();
        void OnEvent(SDL_Event& event);
        const char* GetName() override;

        const char* MouseButtonToString(Uint8 buttonType);
        const char* MouseWheelDirectionToString(Uint32 direction);

        static MouseModule* Get();
    };
}

#endif