#pragma once
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <vector>

class AudioMixer {
public:
    AudioMixer() = default;
    ~AudioMixer();

    bool init(int freq = 48000, SDL_AudioFormat fmt = SDL_AUDIO_F32, int channels = 2);
    void shutdown();

    bool loadSound(int key, const std::string& path);            // wav/mp3/etc.
    MIX_Track* play(int key, float volume01 = 1.0f);             // overlay okay

    void setTrackVolume(MIX_Track* track, float volume01);       // per instance
    void setMasterVolume(float volume01);                        // mixer-wide

private:
    MIX_Mixer* m_mixer = nullptr;
    std::unordered_map<int, MIX_Audio*> m_audio;                 // cached
    std::vector<MIX_Track*> m_tracks;                            // optional
};
