#ifndef WORLD2D_LUA_ENUMS_EASINGSTYLE_H
#define WORLD2D_LUA_ENUMS_EASINGSTYLE_H

namespace world2d {
    enum EasingStyle {
        EasingStyle_Linear,

        EasingStyle_Quadratic,
        EasingStyle_Cubic,
        EasingStyle_Quartic,
        EasingStyle_Quintic,
        EasingStyle_Sextic,
        EasingStyle_Septic,
        EasingStyle_Octic,

        EasingStyle_Back,
        EasingStyle_Bounce,
        EasingStyle_Circle,
        EasingStyle_Elastic,
        EasingStyle_Exponent2,
        EasingStyle_Sine,
        EasingStyle_ExponentE,
        EasingStyle_Log10,
        EasingStyle_SquareRoot,
    };
}

#endif