// Use with caution: some easing styles don't work as intented

#define _USE_MATH_DEFINES

#include "world2d/modules/TweeningModule.h"
#include "world2d/lua/structures/Tween.h"

#include "world2d/lua/enums/EasingStyle.h"
#include "world2d/lua/enums/EasingDirection.h"

#include <unordered_map>
#include <cmath>
#include <algorithm>

world2d::TweeningModule::TweeningModule() : world2d::Module() {
    
}

bool world2d::TweeningModule::Initialize() {
    sol::state& lua = mEngine->GetLua();

    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
    sol::table luaTweeningNamespace { lua.create_table() };

    luaTweeningNamespace.new_enum("EasingStyle",
        "Linear", EasingStyle_Linear,
        
        "Quadratic", EasingStyle_Quadratic,
        "Cubic", EasingStyle_Cubic,
        "Quartic", EasingStyle_Quartic,
        "Quintic", EasingStyle_Quintic,
        "Sextic", EasingStyle_Sextic,
        "Septic", EasingStyle_Septic,
        "Octic", EasingStyle_Octic,

        "Back", EasingStyle_Back,
        "Bounce", EasingStyle_Bounce,
        "Circle", EasingStyle_Circle,
        "Elastic", EasingStyle_Elastic,
        "Exponent2", EasingStyle_Exponent2,
        "Sine", EasingStyle_Sine,
        "ExponentE", EasingStyle_ExponentE,
        "Log10", EasingStyle_Log10,
        "SquareRoot", EasingStyle_SquareRoot
    );

    luaTweeningNamespace.new_enum("EasingDirection",
        "In", EasingDirection_In,
        "InOut", EasingDirection_InOut,
        "Out", EasingDirection_Out
    );

    luaTweeningNamespace.new_usertype<world2d::Tween>("Tween",
        sol::constructors<world2d::Tween(sol::lua_value, world2d::EasingStyle, world2d::EasingDirection, double, sol::table)>(),

        "Play",
        &world2d::Tween::Play,

        "Pause",
        &world2d::Tween::Pause,

        sol::meta_function::garbage_collect,
        [&](world2d::Tween* tween) {
            RemoveTween(tween);
        }
    );

    luaWorld2dNamespace["Tweening"] = luaTweeningNamespace;
    return true;
}

void world2d::TweeningModule::Update(double dt) {
    for (world2d::Tween* tween : mTweens) {
        tween->Update(dt);
    }
}

const char* world2d::TweeningModule::GetName() {
    return "TweeningModule";
}

void world2d::TweeningModule::AddTween(world2d::Tween* tween) {
    mTweens.push_back(tween);
}

void world2d::TweeningModule::RemoveTween(world2d::Tween* tween) {
    mTweens.erase(std::find(mTweens.begin(), mTweens.end(), tween));
}

world2d::TweeningModule* world2d::TweeningModule::Get() {
    static world2d::TweeningModule currentModule;
    return &currentModule;
}

T_EasingFunctionsMap& world2d::TweeningModule::GetEasingFunctions() {
    static T_EasingFunctionsMap easingFunctions {
        {EasingDirection_In, std::unordered_map<world2d::EasingStyle, EasingFunction> {
            {EasingStyle_Linear, [](double p) {
                return p;
            }},

            {EasingStyle_Quadratic, [](double p) {
                return p * p;
            }},

            {EasingStyle_Cubic, [](double p) {
                return p * p * p;
            }},

            {EasingStyle_Quartic, [](double p) {
                return p * p * p * p;
            }},

            {EasingStyle_Quintic, [](double p) {
                return p * p * p * p * p;
            }},

            {EasingStyle_Sextic, [](double p) {
                return p * p * p * p * p * p;
            }},

            {EasingStyle_Septic, [](double p) {
                return p * p * p * p * p * p * p;
            }},

            {EasingStyle_Octic, [](double p) {
                return p * p * p * p * p * p * p * p;
            }},

            {EasingStyle_Back, [](double p) {
                constexpr double k = 1.70158;
                return p * p * (p * (k + 1) - k);
            }},

            {EasingStyle_Bounce, [](double p) {
                return 1 - easingFunctions[EasingDirection_Out][EasingStyle_Bounce](1 - p);
            }},

            {EasingStyle_Circle, [](double p) {
                return 1 - std::sqrt(1 - p * p);
            }},

            {EasingStyle_Elastic, [](double p) {
                const float m = p - 1;
                return -std::pow(2, 10 * m) * std::sin((m * 40 - 3) * M_PI / 6);
            }},

            {EasingStyle_Exponent2, [](double p) {
                if (p <= 0) return 0.0;
                return std::pow(2.0, 10 * (p - 1));
            }},

            {EasingStyle_Sine, [](double p) {
                return 1.0 - std::cos(p * M_PI * 0.5);
            }},

            {EasingStyle_ExponentE, [](double p) {
                if (p <= 0) return 0.0;
                return std::pow(M_E, -10 * (1 - p));
            }},

            {EasingStyle_Log10, [](double p) {
                return 1 - easingFunctions[EasingDirection_Out][EasingStyle_Log10](1 - p);
            }},

            {EasingStyle_SquareRoot, [](double p) {
                return 1 - easingFunctions[EasingDirection_Out][EasingStyle_SquareRoot](1 - p);
            }}
        }},

        {EasingDirection_InOut, std::unordered_map<world2d::EasingStyle, EasingFunction> {
            {EasingStyle_Linear, [](double p) {
                return p;
            }},

            {EasingStyle_Quadratic, [](double p) {
                const double m = p - 1;
                const double t = p * 2;
                if (t < 1) return p * t;
                return 1 - m * m;
            }},

            {EasingStyle_Cubic, [](double p) {
                const double m = p - 1;
                const double t = p * 2;
                if (t < 1) return p * t * t;
                return 1 + m * m * m;
            }},

            {EasingStyle_Quartic, [](double p) {
                const double m = p - 1;
                const double t = p * 2;
                if (t < 1) return p * t * t * t;
                return 1 - m * m * m * m;
            }},

            {EasingStyle_Quintic, [](double p) {
                const double m = p - 1;
                const double t = p * 2;
                if (t < 1) return p * t * t * t * t;
                return 1 + m * m * m * m * m;
            }},

            {EasingStyle_Sextic, [](double p) {
                const double m = p - 1;
                const double t = p * 2;
                if (t < 1) return p * t * t * t * t * t;
                return 1 - m * m * m * m * m * m;
            }},

            {EasingStyle_Septic, [](double p) {
                const double m = p - 1;
                const double t = p * 2;
                if (t < 1) return p * t * t * t * t * t * t;
                return 1 + m * m * m * m * m * m * m;
            }},

            {EasingStyle_Octic, [](double p) {
                const double m = p - 1;
                const double t = p * 2;
                if (t < 1) return p * t * t * t * t * t * t * t;
                return 1 - m * m * m * m * m * m * m * m;
            }},

            {EasingStyle_Back, [](double p) {
                const double m = p - 1;
                const double t = p * 2;
                const double k = 1.70158 * 1.525;
                if (p < 0.5) return p * t * (t * (k + 1) - k);
                return 1 + 2 * m * m * (2 * m * (k + 1) + k);
            }},

            {EasingStyle_Bounce, [](double p) {
                const double t = p * 2;
                if (t < 1) return 0.5 - 0.5 * easingFunctions[EasingDirection_Out][EasingStyle_Bounce](1 - t);
                return 0.5 + 0.5 * easingFunctions[EasingDirection_Out][EasingStyle_Bounce](t - 1);
            }},

            {EasingStyle_Circle, [](double p) {
                const double m = p - 1;
                const double t = p * 2;
                if (t < 1) return (1 - std::sqrt(1 - t * t)) * 0.5;
                return (std::sqrt(1 - 4 * m * m) + 1) * 0.5;
            }},

            {EasingStyle_Elastic, [](double p) {
                const double s = 2 * p - 1;
                const double k = (80 * s - 9) * M_PI / 18;
                if (s < 0) return -0.5 * std::pow(2, 10 * s) * std::sin(k);
                return 1 + 0.5 * std::pow(2, -10 * s) * std::sin(k);
            }},

            {EasingStyle_Exponent2, [](double p) {
                if (p <= 0) return 0.0;
                if (p >= 1) return 1.0;
                if (p < 0.5) return std::pow(2, 10 * (2 * p - 1) - 1);
                return 1 - std::pow(2, -10 * (2 * p - 1) - 1);
            }},

            {EasingStyle_Sine, [](double p) {
                return 0.5 * (1 - std::cos(p * M_PI));
            }},

            {EasingStyle_ExponentE, [](double p) {
                const double t = p * 2;
                if (t < 1) return 0.5 - 0.5 * easingFunctions[EasingDirection_Out][EasingStyle_ExponentE](1 - t);
                return 0.5 + 0.5 * easingFunctions[EasingDirection_Out][EasingStyle_ExponentE](t - 1);
            }},

            {EasingStyle_Log10, [](double p) {
                const double t = p * 2;
                if (t < 1) return 0.5 - 0.5 * easingFunctions[EasingDirection_Out][EasingStyle_Log10](1 - t);
                return 0.5 + 0.5 * easingFunctions[EasingDirection_Out][EasingStyle_Log10](t - 1);
            }},

            { EasingStyle_SquareRoot, [](double p) {
                const double t = p * 2;
                if (t < 1) return 0.5 - 0.5 * easingFunctions[EasingDirection_Out][EasingStyle_SquareRoot](1 - t);
                return 0.5 + 0.5 * easingFunctions[EasingDirection_Out][EasingStyle_SquareRoot](t - 1);
            }}
        }},

        { EasingDirection_Out, {
            {EasingStyle_Linear, [](double p) {
                return p;
            }},

            {EasingStyle_Quadratic, [](double p) {
                const double m = p - 1;
                return 1 - m * m;
            }},

            {EasingStyle_Cubic, [](double p) {
                const double m = p - 1;
                return 1 + m * m * m;
            }},

            {EasingStyle_Quartic, [](double p) {
                const double m = p - 1;
                return 1 - m * m * m * m;
            }},

            {EasingStyle_Quintic, [](double p) {
                const double m = p - 1;
                return 1 + m * m * m * m * m;
            }},

            {EasingStyle_Sextic, [](double p) {
                const double m = p - 1;
                return 1 - m * m * m * m * m * m;
            }},

            {EasingStyle_Septic, [](double p) {
                const double m = p - 1;
                return 1 + m * m * m * m * m * m * m;
            }},

            {EasingStyle_Octic, [](double p) {
                const double m = p - 1;
                return 1 - m * m * m * m * m * m * m * m;
            }},

            {EasingStyle_Back, [](double p) {
                const double m = p - 1;
                constexpr double k = 1.70158;
                return 1 + m * m * (m * (k + 1) + k);
            }},

            {EasingStyle_Bounce, [](double p) {
                constexpr double r = 1 / 2.75;
                const double k1 = r;
                const double k2 = 2 * r;
                const double k3 = 1.5 * r;
                const double k4 = 2.5 * r;
                const double k5 = 2.25 * r;
                const double k6 = 2.625 * r;
                const double k0 = 7.5625;
                double t = 0;

                if (p < k1) return k0 * p * p;
                else if (p < k2) { t = p - k3; return k0 * t * t + 0.75; }
                else if (p < k4) { t = p - k5; return k0 * t * t + 0.9375; }
                
                t = p - k6;
                return k0 * t * t * 0.984375;
            }},

            {EasingStyle_Circle, [](double p) {
                const double m = p - 1;
                return std::sqrt(1 - m * m);
            }},

            {EasingStyle_Elastic, [](double p) {
                return 1 + (std::pow(2, 10 * -p) * std::sin((-p * 40 / 3) * M_PI / 6));
            }},

            {EasingStyle_Exponent2, [](double p) {
                if (p >= 1) return 1.0;
                return 1 - std::pow(2, -10 * p);
            }},

            {EasingStyle_Sine, [](double p) {
                return std::sin(p * M_PI * 0.5);
            }},

            {EasingStyle_ExponentE, [](double p) {
                return 1 - easingFunctions[EasingDirection_In][EasingStyle_ExponentE](1 - p);
            }},

            {EasingStyle_Log10, [](double p) {
                return std::log10((p * 9) + 1);
            }},

            {EasingStyle_SquareRoot, [](double p) {
                return std::sqrt(p);
            }}
        }}
    };

    return easingFunctions;
}