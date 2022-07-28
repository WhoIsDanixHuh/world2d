#include "world2d/modules/AudioModule.h"
#include "world2d/lua/structures/Audio.h"

#include "miniaudio/miniaudio.h"

world2d::AudioModule::AudioModule() : world2d::Module() {

}

world2d::AudioModule::~AudioModule() {
    ma_engine_uninit(&maEngine);
}

bool world2d::AudioModule::Initialize() {
    if (ma_engine_init(nullptr, &maEngine) != MA_SUCCESS) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize miniaudio engine.");
        return false;
    }

    sol::state& lua = mEngine->GetLua();
    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };

    luaWorld2dNamespace.new_usertype<world2d::Audio>("Audio",
        sol::constructors<world2d::Audio(const char*)>(),

        "Play",
        &world2d::Audio::Play,

        "Pause",
        &world2d::Audio::Pause,

        "Stop",
        &world2d::Audio::Stop,

        "volume", sol::property(
            [&](world2d::Audio& self) {
                return self.GetVolume();
            },

            [&](world2d::Audio& self, float volume) {
                return self.SetVolume(volume);
            }
        ),

        "pitch", sol::property(
            [&](world2d::Audio& self) {
                return self.GetPitch();
            },

            [&](world2d::Audio& self, float pitch) {
                self.SetPitch(pitch);
            }
        ),

        "isPlaying", sol::property([&](world2d::Audio& self) {
            return self.IsPlaying();
        }),

        "isLooping", sol::property(
            [&](world2d::Audio& self) {
                return self.IsLooping();
            },

            [&](world2d::Audio& self, bool looping) {
                self.SetLooping(looping);
            }
        )
    );

    return true;
}

const char* world2d::AudioModule::GetName() {
    return "AudioModule";
}

ma_engine* world2d::AudioModule::GetMiniAudioEngine() {
    return &maEngine;
}

world2d::AudioModule* world2d::AudioModule::Get() {
    static world2d::AudioModule currentModule;
    return &currentModule;
}