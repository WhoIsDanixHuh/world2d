#include "world2d/modules/MouseModule.h"

#include <string>
#include <tuple>

world2d::MouseModule::MouseModule() : world2d::Module() {

}

bool world2d::MouseModule::Initialize() {
    sol::state& lua = mEngine->GetLua();

    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
    sol::table luaMouseNamespace { lua.create_table() };

    luaWorld2dNamespace.set_function("OnMousePressed", [&]() {});
    luaWorld2dNamespace.set_function("OnMouseReleased", [&]() {});
    luaWorld2dNamespace.set_function("OnMouseMotion", [&]() {});
    luaWorld2dNamespace.set_function("OnMouseWheelMotion", [&]() {});

    luaMouseNamespace.set_function("GetCoordinates", [&]() {
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        return std::make_tuple(x, y);
    });

    luaWorld2dNamespace["Mouse"] = luaMouseNamespace;
    return true;
}

void world2d::MouseModule::OnEvent(SDL_Event& event) {
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
            const char* funcName = (event.type == SDL_MOUSEBUTTONDOWN) ? "OnMousePressed" : "OnMouseReleased";
            const char* buttonName = MouseButtonToString(event.button.button);

            mEngine->GetLua().get<sol::table>("world2d").get<sol::function>(funcName)(event.button.x, event.button.y, buttonName);
            break;
        }

        case SDL_MOUSEMOTION: {
            mEngine->GetLua().get<sol::table>("world2d").get<sol::function>("OnMouseMotion")(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
            break;
        }

        case SDL_MOUSEWHEEL: {
            mEngine->GetLua().get<sol::table>("world2d").get<sol::function>("OnMouseWheelMotion")(event.wheel.x, event.wheel.y, MouseWheelDirectionToString(event.wheel.direction), event.wheel.preciseX, event.wheel.preciseY);
            break;
        }
    }
}

const char* world2d::MouseModule::MouseButtonToString(Uint8 buttonType) {
    switch (buttonType) {
        case SDL_BUTTON_LEFT: return "Left";
        case SDL_BUTTON_MIDDLE: return "Middle";
        case SDL_BUTTON_RIGHT: return "Right";
    }

    return nullptr;
}

const char* world2d::MouseModule::MouseWheelDirectionToString(Uint32 direction) {
    switch (direction) {
        case SDL_MOUSEWHEEL_NORMAL: return "Normal";
        case SDL_MOUSEWHEEL_FLIPPED: return "Flipped";
    }

    return nullptr;
}

world2d::MouseModule* world2d::MouseModule::Get() {
    static world2d::MouseModule currentModule;
    return &currentModule;
}