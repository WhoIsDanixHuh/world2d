#ifndef WORLD2D_MODULES_CLIPBOARDMODULE_H
#define WORLD2D_MODULES_CLIPBOARDMODULE_H

#include "world2d/Module.h"

namespace world2d {
    class ClipboardModule : public world2d::Module {
    public:
        ClipboardModule();
        ClipboardModule(const ClipboardModule&) = delete;

        bool Initialize() override;
        const char* GetName() override;

        static ClipboardModule* Get();
    };
}

#endif