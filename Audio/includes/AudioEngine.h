#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include <memory>

struct DecodedAudio {
    SDL_AudioSpec spec;      // source format (freq, format, channels)
    std::vector<uint8_t> pcm; // interleaved PCM (matches spec.format)
};

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    bool init(int freq = 48000, SDL_AudioFormat fmt = SDL_AUDIO_F32, int channels = 2);
    void shutdown();

    // Play once. Returns a handle ID (for later volume changes), or -1 on error.
    int play(const DecodedAudio& audio, float volume = 1.0f);

    // Volume: 0..1. (If stream supports it natively, we use it; else we scale.)
    void setStreamVolume(int handle, float volume);
    void setMasterVolume(float volume); // scales all new plays; does not retroactively change existing unless you re-set them.

    bool isValid(int handle) const;

private:
    struct PlayingStream {
        SDL_AudioStream* stream = nullptr;
        float volume = 1.0f;
        bool usesNativeGain = false;
    };

    SDL_AudioDeviceID m_device = 0;
    SDL_AudioSpec     m_deviceSpec{};
    float             m_master = 1.0f;

    std::vector<std::unique_ptr<PlayingStream>> m_streams;

    // Helper: try to set stream gain if available at runtime.
    static bool setNativeGain(SDL_AudioStream* s, float gain);
};
