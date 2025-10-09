#pragma once
#include <string>
#include "AudioEngine.h"

namespace AudioLoader {
    bool loadWavFile(const std::string& filePath, DecodedAudio& decodedOutput);
    bool loadMp3File(const std::string& filePath, DecodedAudio& decodedOutput);

    // Convenience function to load any supported format
    bool loadAudioFile(const std::string& filePath, DecodedAudio& decodedOutput);
}
