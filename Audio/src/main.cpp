#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "AudioMixer.h"

namespace {
    constexpr int SOUND_KEY_MIN = 1;
    constexpr int SOUND_KEY_MAX = 5;
    constexpr float DEFAULT_VOLUME = 1.0f;

    void printUsageInstructions() {
        std::cout <<
            "Audio Mixer Demo - Available Commands:\n"
            "  1-5         -> Play sound with that key (sounds will overlay)\n"
            "  master=X    -> Set master volume (0.0 to 1.0)\n"
            "  tN=X        -> Set volume of track N to X (0.0 to 1.0)\n"
            "  q/quit/exit -> Quit the program\n"
            "\n";
    }

    bool isSoundKeyCommand(const std::string& input, int& soundKey) {
        if (input.length() != 1) {
            return false;
        }

        const char keyChar = input[0];
        if (keyChar >= '1' && keyChar <= '5') {
            soundKey = keyChar - '0';
            return true;
        }

        return false;
    }

    bool isMasterVolumeCommand(const std::string& input, float& volume) {
        const std::string prefix = "master=";
        if (input.find(prefix) != 0 || input.length() <= prefix.length()) {
            return false;
        }

        try {
            volume = std::stof(input.substr(prefix.length()));
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }

    bool isTrackVolumeCommand(const std::string& input, int& trackIndex, float& volume) {
        if (input.empty() || input[0] != 't') {
            return false;
        }

        const size_t equalPos = input.find('=');
        if (equalPos == std::string::npos || equalPos <= 1) {
            return false;
        }

        try {
            trackIndex = std::stoi(input.substr(1, equalPos - 1));
            volume = std::stof(input.substr(equalPos + 1));
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }

    bool isQuitCommand(const std::string& input) {
        return input == "q" || input == "quit" || input == "exit";
    }

    bool loadDemoSounds(AudioMixer& mixer) {
        const std::vector<std::pair<int, std::string>> soundFiles = {
            {1, "assets/sound.wav"},
            {2, "assets/sound2.wav"},
            {3, "assets/sound3.wav"},
            {4, "assets/sound4.mp3"},
            {5, "assets/sound5.mp3"}
        };

        for (const auto& [key, path] : soundFiles) {
            if (!mixer.loadAudioFile(key, path)) {
                std::cout << "Warning: Could not load " << path << std::endl;
            }
        }

        return true;
    }
}

int main() {
    AudioMixer audioMixer;

    if (!audioMixer.initialize()) {
        std::cerr << "Failed to initialize audio mixer" << std::endl;
        return 1;
    }

    if (!loadDemoSounds(audioMixer)) {
        std::cerr << "Failed to load demo sounds" << std::endl;
        return 1;
    }

    printUsageInstructions();

    std::vector<MIX_Track*> activeTracks;
    std::string userInput;

    while (std::cout << "> " && std::getline(std::cin, userInput)) {
        if (isQuitCommand(userInput)) {
            break;
        }

        int soundKey;
        if (isSoundKeyCommand(userInput, soundKey)) {
            MIX_Track* newTrack = audioMixer.playSound(soundKey, DEFAULT_VOLUME);
            if (newTrack) {
                activeTracks.push_back(newTrack);
                std::cout << "Playing sound " << soundKey
                         << " (track #" << activeTracks.size() - 1 << ")" << std::endl;
            } else {
                std::cout << "Failed to play sound " << soundKey << std::endl;
            }
            continue;
        }

        float volume;
        if (isMasterVolumeCommand(userInput, volume)) {
            audioMixer.setMasterVolume(volume);
            std::cout << "Master volume set to " << volume << std::endl;
            continue;
        }

        int trackIndex;
        if (isTrackVolumeCommand(userInput, trackIndex, volume)) {
            if (trackIndex >= 0 &&
                trackIndex < static_cast<int>(activeTracks.size()) &&
                activeTracks[trackIndex]) {
                audioMixer.setTrackVolume(activeTracks[trackIndex], volume);
                std::cout << "Track " << trackIndex << " volume set to " << volume << std::endl;
            } else {
                std::cout << "Invalid track index: " << trackIndex << std::endl;
            }
            continue;
        }

        std::cout << "Unknown command. " << std::endl;
        printUsageInstructions();
    }

    audioMixer.shutdown();
    return 0;
}
