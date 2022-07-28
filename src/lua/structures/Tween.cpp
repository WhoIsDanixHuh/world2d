#include "world2d/lua/structures/Tween.h"

#include "world2d/Engine.h"
#include "world2d/modules/TweeningModule.h"

#include <cmath>

inline double lerp(double a, double b, double f) {
    return a + f * (b - a);
}

world2d::Tween::Tween(sol::lua_value data_, world2d::EasingStyle easingStyle_, world2d::EasingDirection easingDirection_, double t_, sol::table properties_)
    : easingStyle(easingStyle_),
      easingDirection(easingDirection_),
      t(t_),
      properties(properties_)
{
    sol::state& lua = world2d::Engine::Get()->GetLua();
    
    if (!data_.is<sol::table>() && !data_.is<sol::userdata>()) {
        luaL_error(lua.lua_state(), "Failed to create tween: data is not a table or userdata");
    }
    
    data = data_.as<sol::table>();
    oldData = lua.create_table();

    for (const auto& pair : data) {
        if (pair.first.get_type() == sol::type::string && pair.second.get_type() == sol::type::number) {
            oldData[pair.first.as<const char*>()] = pair.second.as<double>();
        }
    }

    world2d::TweeningModule::Get()->AddTween(this);
}

void world2d::Tween::Update(double dt) {
    if (!playing) {
        return;
    }

    if (ct >= t) {
        playing = false;
        ct = 0;
        return;
    }

    ct += (dt / 1000);

    T_EasingFunctionsMap& easingFunctions = world2d::TweeningModule::Get()->GetEasingFunctions();
    p = easingFunctions[easingDirection][easingStyle](std::clamp(ct / t, 0.0, 1.0));

    for (const auto& pair : oldData) {
        const char* key = pair.first.as<const char*>();
        data[key] = lerp(pair.second.as<double>(), properties.get<double>(key), p);
    }
}

void world2d::Tween::Play() {
    playing = true;
}

void world2d::Tween::Pause() {
    playing = false;
}

bool world2d::Tween::operator==(const world2d::Tween& tween) {
    return (data.pointer() == tween.data.pointer() &&
        oldData.pointer() == tween.oldData.pointer() &&
        easingStyle == tween.easingStyle &&
        easingDirection == tween.easingDirection &&
        ct == tween.ct &&
        t == tween.t &&
        properties.pointer() == tween.properties.pointer() &&
        p == tween.p);
}