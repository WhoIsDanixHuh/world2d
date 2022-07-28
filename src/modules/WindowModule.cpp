#include "world2d/modules/WindowModule.h"
#include <tuple>

world2d::WindowModule::WindowModule() : world2d::Module() {

}

bool world2d::WindowModule::Initialize() {
    sol::state& lua = mEngine->GetLua();

    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
    sol::table luaWindowNamespace { lua.create_table() };

    // ===== Enums =====
    luaWindowNamespace.new_enum("MessageBoxType",
        "Error", SDL_MESSAGEBOX_ERROR,
        "Warning", SDL_MESSAGEBOX_WARNING,
        "Information", SDL_MESSAGEBOX_INFORMATION
    );

    luaWindowNamespace.new_enum("FlashOperation",
        "Cancel", SDL_FLASH_CANCEL,
        "Briefly", SDL_FLASH_BRIEFLY,
        "UntilFocused", SDL_FLASH_UNTIL_FOCUSED
    );
    // =================

    // ===== Events =====
    constexpr int EVENTS_ARRAY_LENGTH = 14;
    const char* events[EVENTS_ARRAY_LENGTH] = {
        "OnWindowShown",
        "OnWindowHidden",
        "OnWindowExposed",
        "OnWindowMoved",
        "OnWindowRezised",
        "OnWindowSizeChanged",
        "OnWindowMinimized",
        "OnWindowMaximized",
        "OnWindowRestored",
        "OnWindowMouseEnter",
        "OnWindowMouseLeave",
        "OnWindowKeyboardFocusGained",
        "OnWindowKeyboardFocusLost",
        "OnWindowClose"
    };

    for (int i = 0; i < EVENTS_ARRAY_LENGTH; ++i) {
        luaWorld2dNamespace.set_function(events[i], []() {});
    }
    // ==================

    // ===== Main functions =====
    luaWindowNamespace.set_function("SetPosition", [&](int x, int y) {
        SDL_SetWindowPosition(mEngine->GetSDLWindow(), x, y);
    });

    luaWindowNamespace.set_function("SetSize", [&](int w, int h) {
        SDL_SetWindowSize(mEngine->GetSDLWindow(), w, h);
    });

    luaWindowNamespace.set_function("GetSize", [&]() {
        int w, h;
        SDL_GetWindowSize(mEngine->GetSDLWindow(), &w, &h);
        return std::make_tuple(w, h);
    });

    luaWindowNamespace.set_function("SetTitle", [&](const char* title) {
        SDL_SetWindowTitle(mEngine->GetSDLWindow(), title);
    });

    luaWindowNamespace.set_function("GetTitle", [&]() {
        return SDL_GetWindowTitle(mEngine->GetSDLWindow());
    });

    luaWindowNamespace.set_function("SetResizable", [&](SDL_bool resizable) {
        SDL_SetWindowResizable(mEngine->GetSDLWindow(), resizable);
    });

    luaWindowNamespace.set_function("ShowSimpleMessageBox", [&](SDL_MessageBoxFlags flags, const char* title, const char* message) {
        if (SDL_ShowSimpleMessageBox(flags, title, message, mEngine->GetSDLWindow()) != 0) {
            luaL_error(lua.lua_state(), SDL_GetError());
        }
    });

    luaWindowNamespace.set_function("Flash", [&](SDL_FlashOperation operation) {
        if (SDL_FlashWindow(mEngine->GetSDLWindow(), operation) != 0) {
            luaL_error(lua.lua_state(), SDL_GetError());
        }
    });

    luaWindowNamespace.set_function("SetVSync", [&](bool vsync) {
        if (SDL_RenderSetVSync(mEngine->GetSDLRenderer(), vsync) != 0) {
            luaL_error(lua.lua_state(), SDL_GetError());
        }
    });

    luaWindowNamespace.set_function("GetDisplaySize", [&]() {
        SDL_DisplayMode mode;
        SDL_GetCurrentDisplayMode(0, &mode);
        return std::make_tuple(mode.w, mode.h);
    });
    // ==========================

    luaWorld2dNamespace["Window"] = luaWindowNamespace;
    return true;
}

void world2d::WindowModule::OnEvent(SDL_Event& event) {
    if (event.type != SDL_WINDOWEVENT) return;

    sol::table luaWorld2dNamespace { mEngine->GetLua().get<sol::table>("world2d") };

    switch (event.window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            luaWorld2dNamespace.get<sol::function>("OnWindowShown")();
            break;

        case SDL_WINDOWEVENT_HIDDEN:
            luaWorld2dNamespace.get<sol::function>("OnWindowHidden")();
            break;

        case SDL_WINDOWEVENT_EXPOSED:
            luaWorld2dNamespace.get<sol::function>("OnWindowExposed")();
            break;

        case SDL_WINDOWEVENT_MOVED:
            luaWorld2dNamespace.get<sol::function>("OnWindowMoved")(event.window.data1, event.window.data2);
            break;

        case SDL_WINDOWEVENT_RESIZED:
            luaWorld2dNamespace.get<sol::function>("OnWindowResized")(event.window.data1, event.window.data2);
            break;

        case SDL_WINDOWEVENT_SIZE_CHANGED:
            luaWorld2dNamespace.get<sol::function>("OnWindowSizeChanged")(event.window.data1, event.window.data2);
            break;

        case SDL_WINDOWEVENT_MINIMIZED:
            luaWorld2dNamespace.get<sol::function>("OnWindowMinimized")();
            break;

        case SDL_WINDOWEVENT_MAXIMIZED:
            luaWorld2dNamespace.get<sol::function>("OnWindowMaximized")();
            break;

        case SDL_WINDOWEVENT_RESTORED:
            luaWorld2dNamespace.get<sol::function>("OnWindowRestored")();
            break;

        case SDL_WINDOWEVENT_ENTER:
            luaWorld2dNamespace.get<sol::function>("OnWindowMouseEnter")();
            break;

        case SDL_WINDOWEVENT_LEAVE:
            luaWorld2dNamespace.get<sol::function>("OnWindowMouseLeave")();
            break;

        case SDL_WINDOWEVENT_FOCUS_GAINED:
            luaWorld2dNamespace.get<sol::function>("OnWindowKeyboardFocusGained")();
            break;

        case SDL_WINDOWEVENT_FOCUS_LOST:
            luaWorld2dNamespace.get<sol::function>("OnWindowKeyboardFocusLost")();
            break;

        case SDL_WINDOWEVENT_CLOSE:
            luaWorld2dNamespace.get<sol::function>("OnWindowClose")();
            break;
    }
}

const char* world2d::WindowModule::GetName() {
    return "WindowModule";
}

world2d::WindowModule* world2d::WindowModule::Get() {
    static world2d::WindowModule currentModule;
    return &currentModule;
}