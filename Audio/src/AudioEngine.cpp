#include "AudioEngine.h"
#include <algorithm>
#include <cstring>

#if !defined(SDL_AUDIO_USES_F32)
#define SDL_AUDIO_USES_F32 1
#endif

AudioEngine::AudioEngine() = default;
AudioEngine::~AudioEngine() { shutdown(); }

bool AudioEngine::init(int freq, SDL_AudioFormat fmt, int channels) {
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        SDL_Log("SDL audio init failed: %s", SDL_GetError());
        return false;
    }

    SDL_AudioSpec desired{};
    desired.freq = freq;
    desired.format = fmt;        // SDL_AUDIO_F32 (float) is a great default
    desired.channels = (Uint8)channels;

    // Open default playback device in paused state (streams can resume it)
    m_device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &desired);
    if (!m_device) {
        SDL_Log("OpenAudioDevice failed: %s", SDL_GetError());
        return false;
    }
    m_deviceSpec = desired;
    SDL_ResumeAudioDevice(m_device);
    return true;
}

void AudioEngine::shutdown() {
    for (auto& p : m_streams) {
        if (p && p->stream) SDL_DestroyAudioStream(p->stream);
    }
    m_streams.clear();
    if (m_device) {
        SDL_CloseAudioDevice(m_device);
        m_device = 0;
    }
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

bool AudioEngine::setNativeGain(SDL_AudioStream* s, float gain) {
    // SDL3 has SDL_SetAudioStreamGain(). If present, use it; otherwise return false.
    // We avoid a hard link-time requirement by just calling it directly; if your SDL3 is recent, it will exist.
    // If not, comment this out and always return false to use software scaling.
#if defined(SDL_VERSION_ATLEAST)
    // Assume available; if your headers are old, remove this block and fallback.
    if (SDL_SetAudioStreamGain(s, gain)) {
        return true;
    }
#else
    (void)s; (void)gain;
#endif
    return false;
}

int AudioEngine::play(const DecodedAudio& audio, float volume) {
    if (!m_device) return -1;

    // Create a stream bound to our playback device, with conversion as needed.
    SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(
        m_device,
        &audio.spec,    // source format
        nullptr,        // no callback
        nullptr
    );
    if (!stream) {
        SDL_Log("OpenAudioDeviceStream failed: %s", SDL_GetError());
        return -1;
    }

    // Volume handling
    auto handle = std::make_unique<PlayingStream>();
    handle->stream = stream;
    handle->volume = std::clamp(volume * m_master, 0.0f, 1.0f);
    handle->usesNativeGain = setNativeGain(stream, handle->volume);

    // If no native gain, scale the PCM before queuing
    const uint8_t* src = audio.pcm.data();
    const size_t   len = audio.pcm.size();

    if (handle->usesNativeGain) {
        SDL_PutAudioStreamData(stream, src, (int)len);
    } else {
        // software gain: copy & scale into temporary buffer (float32 only; else convert in a pinch)
        if (audio.spec.format == SDL_AUDIO_F32) {
            std::vector<uint8_t> scaled(len);
            const float* in  = reinterpret_cast<const float*>(src);
            float*       out = reinterpret_cast<float*>(scaled.data());
            size_t frames = len / sizeof(float);
            for (size_t i = 0; i < frames; ++i) {
                out[i] = in[i] * handle->volume;
            }
            SDL_PutAudioStreamData(stream, scaled.data(), (int)scaled.size());
        } else if (audio.spec.format == SDL_AUDIO_S16) {
            std::vector<int16_t> scaled(len / sizeof(int16_t));
            const int16_t* in = reinterpret_cast<const int16_t*>(src);
            for (size_t i = 0; i < scaled.size(); ++i) {
                int v = int(in[i] * handle->volume);
                v = std::clamp(v, -32768, 32767);
                scaled[i] = (int16_t)v;
            }
            SDL_PutAudioStreamData(stream, scaled.data(), (int)(scaled.size()*sizeof(int16_t)));
        } else {
            // Fallback: just push unscaled (volume 1.0)
            SDL_PutAudioStreamData(stream, src, (int)len);
        }
    }

    SDL_FlushAudioStream(stream);
    SDL_ResumeAudioStreamDevice(stream);

    // Save and return index
    m_streams.push_back(std::move(handle));
    return (int)m_streams.size() - 1;
}

void AudioEngine::setStreamVolume(int handle, float volume) {
    if (!isValid(handle)) return;
    volume = std::clamp(volume, 0.0f, 1.0f);
    auto& s = m_streams[handle];
    s->volume = volume;

    if (s->usesNativeGain) {
        setNativeGain(s->stream, volume);
    } else {
        // No native gain; for simplicity we won’t rescale in-flight data here.
        // Next play() will use the updated master *or set per-stream again.
        // Optionally: we could pause, drain, and requeue scaled audio.
    }
}

void AudioEngine::setMasterVolume(float volume) {
    m_master = std::clamp(volume, 0.0f, 1.0f);
}

bool AudioEngine::isValid(int handle) const {
    return handle >= 0 && handle < (int)m_streams.size() && m_streams[handle] && m_streams[handle]->stream;
}
