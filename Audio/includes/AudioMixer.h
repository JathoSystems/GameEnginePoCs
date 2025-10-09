#pragma once
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <vector>

class AudioMixer {
public:
    static constexpr int DEFAULT_FREQUENCY = 48000;
    static constexpr int DEFAULT_CHANNELS = 2;
    static constexpr SDL_AudioFormat DEFAULT_FORMAT = SDL_AUDIO_F32;

    AudioMixer() = default;
    ~AudioMixer();

    bool initialize(
        int frequency = DEFAULT_FREQUENCY,
        SDL_AudioFormat format = DEFAULT_FORMAT,
        int channels = DEFAULT_CHANNELS
    );

    void shutdown();

    bool loadAudioFile(int soundKey, const std::string& filePath);
    MIX_Track* playSound(int soundKey, float volume = 1.0f);

    void setTrackVolume(MIX_Track* track, float volume);
    void setMasterVolume(float volume);

    bool hasSound(int soundKey) const;
    size_t getActiveTrackCount() const { return m_activeTracks.size(); }

private:
    MIX_Mixer* m_mixer = nullptr;
    std::unordered_map<int, MIX_Audio*> m_loadedAudio;
    std::vector<MIX_Track*> m_activeTracks;

    static constexpr float MIN_VOLUME = 0.0f;
    static constexpr float MAX_VOLUME = 1.0f;

    static float clampVolume(float volume) {
        return std::clamp(volume, MIN_VOLUME, MAX_VOLUME);
    }

    void cleanupResources();
    bool initializeSDLAudio(int frequency, SDL_AudioFormat format, int channels);
};
