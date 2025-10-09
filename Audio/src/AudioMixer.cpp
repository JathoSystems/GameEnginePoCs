#include "AudioMixer.h"
#include <algorithm>

static float clamp01(float v){ return std::max(0.0f, std::min(1.0f, v)); }

AudioMixer::~AudioMixer() { shutdown(); }

bool AudioMixer::init(int freq, SDL_AudioFormat fmt, int channels) {
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        SDL_Log("SDL audio init failed: %s", SDL_GetError());
        return false;
    }
    if (!MIX_Init()) { // SDL3_mixer init
        SDL_Log("MIX_Init failed: %s", SDL_GetError());
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return false;
    }

    SDL_AudioSpec hint{};
    hint.freq = freq;
    hint.format = fmt;
    hint.channels = (Uint8)channels;

    m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &hint);
    if (!m_mixer) {
        SDL_Log("MIX_CreateMixerDevice failed: %s", SDL_GetError());
        MIX_Quit();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return false;
    }

    // No MIX_ResumeMixerDevice in SDL3_mixer; mixer is ready after creation.
    return true;
}

void AudioMixer::shutdown() {
    // stop/destroy any tracks
    for (auto* t : m_tracks) {
        if (t) MIX_DestroyTrack(t); // stops immediately and frees the track
    }
    m_tracks.clear();

    // free cached audio
    for (auto& kv : m_audio) {
        if (kv.second) MIX_DestroyAudio(kv.second);
    }
    m_audio.clear();

    if (m_mixer) {
        MIX_DestroyMixer(m_mixer);
        m_mixer = nullptr;
    }
    MIX_Quit();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

bool AudioMixer::loadSound(int key, const std::string& path) {
    if (!m_mixer) return false;

    // SDL3_mixer: pass mixer + predecode flag (true = fully uncompress to PCM once)
    MIX_Audio* a = MIX_LoadAudio(m_mixer, path.c_str(), /*predecode=*/false);
    if (!a) {
        SDL_Log("MIX_LoadAudio failed for %s: %s", path.c_str(), SDL_GetError());
        return false;
    }
    // replace if existed
    if (auto it = m_audio.find(key); it != m_audio.end()) {
        MIX_DestroyAudio(it->second);
    }
    m_audio[key] = a;
    return true;
}

MIX_Track* AudioMixer::play(int key, float volume01) {
    if (!m_mixer) return nullptr;
    auto it = m_audio.find(key);
    if (it == m_audio.end()) return nullptr;

    MIX_Track* track = MIX_CreateTrack(m_mixer);
    if (!track) {
        SDL_Log("MIX_CreateTrack failed: %s", SDL_GetError());
        return nullptr;
    }
    if (!MIX_SetTrackAudio(track, it->second)) {
        SDL_Log("MIX_SetTrackAudio failed: %s", SDL_GetError());
        MIX_DestroyTrack(track);
        return nullptr;
    }

    MIX_SetTrackGain(track, clamp01(volume01)); // per-instance volume

    if (!MIX_PlayTrack(track, /*options=*/0)) {
        SDL_Log("MIX_PlayTrack failed: %s", SDL_GetError());
        MIX_DestroyTrack(track);
        return nullptr;
    }

    m_tracks.push_back(track);
    return track;
}

void AudioMixer::setTrackVolume(MIX_Track* track, float volume01) {
    if (track) MIX_SetTrackGain(track, clamp01(volume01));
}

void AudioMixer::setMasterVolume(float volume01) {
    if (m_mixer) MIX_SetMasterGain(m_mixer, clamp01(volume01));
}
