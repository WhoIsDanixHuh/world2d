#ifndef WORLD2D_LUA_IMGUI_WIDGETS_KEYBOARD_INPUT_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_KEYBOARD_INPUT_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class KeyboardInputWidget : public Widget {
        private:
            KeyboardInputWidget();

        public:
            KeyboardInputWidget(const KeyboardInputWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static KeyboardInputWidget* Get();
        };
    }
}

#endif