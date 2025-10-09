#include "Sound.h"
#include <SDL3/SDL.h>
#include <cstring>
#include <vector>
#include "dr_mp3.h"

// Ensure out.spec is fully set (format, channels, freq).
static void make_spec(SDL_AudioSpec& spec, int freq, SDL_AudioFormat fmt, int channels) {
    spec.freq = freq;
    spec.format = fmt;
    spec.channels = (Uint8)channels;
}

bool Sound::loadWAV(const std::string& path, DecodedAudio& out) {
    SDL_AudioSpec wavSpec{};
    uint8_t*      wavBuf = nullptr;
    uint32_t      wavLen = 0;

    if (!SDL_LoadWAV(path.c_str(), &wavSpec, &wavBuf, &wavLen)) {
        SDL_Log("SDL_LoadWAV failed for %s: %s", path.c_str(), SDL_GetError());
        return false;
    }

    out.spec = wavSpec;
    out.pcm.assign(wavBuf, wavBuf + wavLen);
    SDL_free(wavBuf);
    return true;
}

bool Sound::loadMP3(const std::string& path, DecodedAudio& out) {
    drmp3 mp3{};
    if (!drmp3_init_file(&mp3, path.c_str(), nullptr)) {
        SDL_Log("dr_mp3 failed to open %s", path.c_str());
        return false;
    }

    // Decode to 32-bit float PCM (stereo if source is stereo; keep channels as in file)
    drmp3_uint64 frameCount = drmp3_get_pcm_frame_count(&mp3);
    const int channels = mp3.channels;
    const int sampleRate = (int)mp3.sampleRate;

    std::vector<float> f32;
    f32.resize((size_t)frameCount * channels);
    drmp3_uint64 total = drmp3_read_pcm_frames_f32(&mp3, frameCount, f32.data());
    drmp3_uninit(&mp3);

    // total frames decoded -> bytes
    size_t bytes = (size_t)total * channels * sizeof(float);
    out.pcm.resize(bytes);
    std::memcpy(out.pcm.data(), f32.data(), bytes);

    make_spec(out.spec, sampleRate, SDL_AUDIO_F32, channels);
    return true;
}
