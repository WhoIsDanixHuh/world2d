#include "world2d/modules/AudioModule.h"

#include "world2d/Engine.h"
#include "world2d/lua/structures/Audio.h"

world2d::Audio::Audio(const char* filePath) {
    world2d::AudioModule* audioModule = world2d::AudioModule::Get();
    ma_result result = ma_sound_init_from_file(audioModule->GetMiniAudioEngine(), filePath, 0, nullptr, nullptr, &maSound);

    if (result != MA_SUCCESS) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize sound from file.");
    }
}

world2d::Audio::~Audio() {
    ma_sound_uninit(&maSound);
}

void world2d::Audio::Play() {
    ma_sound_start(&maSound);
}

void world2d::Audio::Pause() {
    ma_sound_stop(&maSound);
}

void world2d::Audio::Stop() {
    ma_sound_stop(&maSound);
    ma_sound_seek_to_pcm_frame(&maSound, 0);
}

void world2d::Audio::SetVolume(float volume) {
    ma_sound_set_volume(&maSound, volume);
}

void world2d::Audio::SetPitch(float pitch) {
    ma_sound_set_pitch(&maSound, pitch);
}

void world2d::Audio::SetLooping(bool looping) {
    ma_sound_set_looping(&maSound, looping);
}

float world2d::Audio::GetVolume() {
    return ma_sound_get_volume(&maSound);
}

float world2d::Audio::GetPitch() {
    return ma_sound_get_pitch(&maSound);
}

bool world2d::Audio::IsPlaying() {
    return ma_sound_is_playing(&maSound);
}

bool world2d::Audio::IsLooping() {
    return ma_sound_is_looping(&maSound);
}