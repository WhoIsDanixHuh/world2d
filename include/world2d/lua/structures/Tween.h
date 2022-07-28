#ifndef WORLD2D_LUA_STRUCTURES_TWEEN_H
#define WORLD2D_LUA_STRUCTURES_TWEEN_H

#include "sol/sol.hpp"

#include "world2d/lua/enums/EasingStyle.h"
#include "world2d/lua/enums/EasingDirection.h"

namespace world2d {
    class Tween {
    private:
        sol::table data;
        sol::table oldData;

        world2d::EasingStyle easingStyle;
        world2d::EasingDirection easingDirection;

        double t = 0.0; // duration
        double ct = 0.0; // current time

        sol::table properties;
        double p = 0.0;

        bool playing = false;

    public:
        Tween(sol::lua_value data, world2d::EasingStyle easingStyle, world2d::EasingDirection easingDirection, double t, sol::table properties);

        void Update(double dt);
        void Play();
        void Pause();

        bool operator==(const world2d::Tween& tween);
    };
}

#endif