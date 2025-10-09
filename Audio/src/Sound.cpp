#include "Sound.h"
#include <SDL3/SDL.h>
#include <cstring>
#include <vector>
#include "dr_mp3.h"

namespace {
    void createAudioSpec(
        SDL_AudioSpec& audioSpec,
        int frequency,
        SDL_AudioFormat format,
        int channels
    ) {
        audioSpec.freq = frequency;
        audioSpec.format = format;
        audioSpec.channels = static_cast<Uint8>(channels);
    }

    bool hasFileExtension(const std::string& filePath, const std::string& extension) {
        if (filePath.length() < extension.length()) {
            return false;
        }

        return filePath.compare(
            filePath.length() - extension.length(),
            extension.length(),
            extension
        ) == 0;
    }
}

bool AudioLoader::loadWavFile(const std::string& filePath, DecodedAudio& decodedOutput) {
    SDL_AudioSpec wavSpec{};
    uint8_t* wavBuffer = nullptr;
    uint32_t wavLength = 0;

    if (!SDL_LoadWAV(filePath.c_str(), &wavSpec, &wavBuffer, &wavLength)) {
        SDL_Log("Failed to load WAV file '%s': %s", filePath.c_str(), SDL_GetError());
        return false;
    }

    decodedOutput.spec = wavSpec;
    decodedOutput.pcmData.assign(wavBuffer, wavBuffer + wavLength);

    SDL_free(wavBuffer);
    return true;
}

bool AudioLoader::loadMp3File(const std::string& filePath, DecodedAudio& decodedOutput) {
    drmp3 mp3Decoder{};

    if (!drmp3_init_file(&mp3Decoder, filePath.c_str(), nullptr)) {
        SDL_Log("Failed to initialize MP3 decoder for file '%s'", filePath.c_str());
        return false;
    }

    const drmp3_uint64 totalFrames = drmp3_get_pcm_frame_count(&mp3Decoder);
    const int channelCount = mp3Decoder.channels;
    const int sampleRate = static_cast<int>(mp3Decoder.sampleRate);

    std::vector<float> floatSamples;
    floatSamples.resize(static_cast<size_t>(totalFrames) * channelCount);

    const drmp3_uint64 framesRead = drmp3_read_pcm_frames_f32(
        &mp3Decoder,
        totalFrames,
        floatSamples.data()
    );

    drmp3_uninit(&mp3Decoder);

    const size_t totalBytes = static_cast<size_t>(framesRead) * channelCount * sizeof(float);
    decodedOutput.pcmData.resize(totalBytes);
    std::memcpy(decodedOutput.pcmData.data(), floatSamples.data(), totalBytes);

    createAudioSpec(decodedOutput.spec, sampleRate, SDL_AUDIO_F32, channelCount);
    return true;
}

bool AudioLoader::loadAudioFile(const std::string& filePath, DecodedAudio& decodedOutput) {
    if (hasFileExtension(filePath, ".wav")) {
        return loadWavFile(filePath, decodedOutput);
    }
    else if (hasFileExtension(filePath, ".mp3")) {
        return loadMp3File(filePath, decodedOutput);
    }
    else {
        SDL_Log("Unsupported audio file format: %s", filePath.c_str());
        return false;
    }
}
