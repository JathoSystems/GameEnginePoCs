#include "AudioMixer.h"
#include <algorithm>

AudioMixer::~AudioMixer() {
    shutdown();
}

bool AudioMixer::initialize(int frequency, SDL_AudioFormat format, int channels) {
    if (!initializeSDLAudio(frequency, format, channels)) {
        return false;
    }

    SDL_AudioSpec audioHint{};
    audioHint.freq = frequency;
    audioHint.format = format;
    audioHint.channels = static_cast<Uint8>(channels);

    m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioHint);
    if (!m_mixer) {
        SDL_Log("Failed to create mixer device: %s", SDL_GetError());
        MIX_Quit();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return false;
    }

    return true;
}

bool AudioMixer::initializeSDLAudio(int frequency, SDL_AudioFormat format, int channels) {
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        SDL_Log("Failed to initialize SDL audio subsystem: %s", SDL_GetError());
        return false;
    }

    if (!MIX_Init()) {
        SDL_Log("Failed to initialize SDL_mixer: %s", SDL_GetError());
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return false;
    }

    return true;
}

void AudioMixer::shutdown() {
    cleanupResources();

    if (m_mixer) {
        MIX_DestroyMixer(m_mixer);
        m_mixer = nullptr;
    }

    MIX_Quit();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void AudioMixer::cleanupResources() {
    for (MIX_Track* track : m_activeTracks) {
        if (track) {
            MIX_DestroyTrack(track);
        }
    }
    m_activeTracks.clear();

    for (auto& [key, audio] : m_loadedAudio) {
        if (audio) {
            MIX_DestroyAudio(audio);
        }
    }
    m_loadedAudio.clear();
}

bool AudioMixer::loadAudioFile(int soundKey, const std::string& filePath) {
    if (!m_mixer) {
        SDL_Log("Mixer not initialized");
        return false;
    }

    MIX_Audio* audioData = MIX_LoadAudio(m_mixer, filePath.c_str(), false);
    if (!audioData) {
        SDL_Log("Failed to load audio file '%s': %s", filePath.c_str(), SDL_GetError());
        return false;
    }

    // Clean up existing audio if key already exists
    auto existingAudio = m_loadedAudio.find(soundKey);
    if (existingAudio != m_loadedAudio.end()) {
        MIX_DestroyAudio(existingAudio->second);
    }

    m_loadedAudio[soundKey] = audioData;
    return true;
}

MIX_Track* AudioMixer::playSound(int soundKey, float volume) {
    if (!m_mixer) {
        SDL_Log("Mixer not initialized");
        return nullptr;
    }

    auto audioIterator = m_loadedAudio.find(soundKey);
    if (audioIterator == m_loadedAudio.end()) {
        SDL_Log("Sound key %d not found", soundKey);
        return nullptr;
    }

    MIX_Track* track = MIX_CreateTrack(m_mixer);
    if (!track) {
        SDL_Log("Failed to create audio track: %s", SDL_GetError());
        return nullptr;
    }

    if (!MIX_SetTrackAudio(track, audioIterator->second)) {
        SDL_Log("Failed to set track audio: %s", SDL_GetError());
        MIX_DestroyTrack(track);
        return nullptr;
    }

    MIX_SetTrackGain(track, clampVolume(volume));

    if (!MIX_PlayTrack(track, 0)) {
        SDL_Log("Failed to play track: %s", SDL_GetError());
        MIX_DestroyTrack(track);
        return nullptr;
    }

    m_activeTracks.push_back(track);
    return track;
}

void AudioMixer::setTrackVolume(MIX_Track* track, float volume) {
    if (track) {
        MIX_SetTrackGain(track, clampVolume(volume));
    }
}

void AudioMixer::setMasterVolume(float volume) {
    if (m_mixer) {
        MIX_SetMasterGain(m_mixer, clampVolume(volume));
    }
}

bool AudioMixer::hasSound(int soundKey) const {
    return m_loadedAudio.find(soundKey) != m_loadedAudio.end();
}
