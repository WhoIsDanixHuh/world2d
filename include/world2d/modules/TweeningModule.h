#ifndef WORLD2D_MODULES_TWEENINGMODULE_H
#define WORLD2D_MODULES_TWEENINGMODULE_H

#include "world2d/Module.h"

#include "world2d/lua/enums/EasingDirection.h"
#include "world2d/lua/enums/EasingStyle.h"
#include <unordered_map>

#include "world2d/lua/structures/Tween.h"
#include <vector>

typedef double(*EasingFunction)(double);
typedef std::unordered_map<world2d::EasingDirection, std::unordered_map<world2d::EasingStyle, EasingFunction>> T_EasingFunctionsMap;

namespace world2d {
    class TweeningModule : public world2d::Module {
    private:
        std::vector<world2d::Tween*> mTweens;

    public:
        TweeningModule();
        TweeningModule(const TweeningModule&) = delete;

        bool Initialize() override;
        void Update(double dt) override;
        const char* GetName() override;

        void AddTween(world2d::Tween* tween);
        void RemoveTween(world2d::Tween* tween);

        static TweeningModule* Get();
        static T_EasingFunctionsMap& GetEasingFunctions();
    };
}

#endif