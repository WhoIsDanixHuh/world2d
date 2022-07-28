#ifndef WORLD2D_LUA_STRUCTURES_AUDIO_H
#define WORLD2D_LUA_STRUCTURES_AUDIO_H

#include "miniaudio/miniaudio.h"

namespace world2d {
    class Audio {
    private:
        ma_sound maSound;
    
    public:
        Audio(const char* filePath);
        ~Audio();

        void Play();
        void Pause();
        void Stop();

        void SetVolume(float volume);
        void SetPitch(float pitch);
        void SetLooping(bool looping);

        float GetVolume();
        float GetPitch();

        bool IsPlaying();
        bool IsLooping();
    };
}

#endif