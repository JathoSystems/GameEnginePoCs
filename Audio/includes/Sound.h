#pragma once
#include <string>
#include "AudioEngine.h"

// Convenience loader that produces DecodedAudio for WAV and MP3.
namespace Sound {
    // Returns true on success.
    bool loadWAV(const std::string& path, DecodedAudio& out);
    bool loadMP3(const std::string& path, DecodedAudio& out);
}
