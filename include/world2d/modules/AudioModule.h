#ifndef WORLD2D_MODULES_AUDIOMODULE_H
#define WORLD2D_MODULES_AUDIOMODULE_H

#include "miniaudio/miniaudio.h"
#include "world2d/Module.h"

namespace world2d {
    class AudioModule : public world2d::Module {
    private:
        ma_engine maEngine;

    public:
        AudioModule();
        AudioModule(const AudioModule&) = delete;
        ~AudioModule();

        bool Initialize() override;
        const char* GetName() override;
        ma_engine* GetMiniAudioEngine();

        static AudioModule* Get();
    };
}

#endif