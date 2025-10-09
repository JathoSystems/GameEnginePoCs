#include <iostream>
#include "AudioMixer.h"

int main() {
    AudioMixer mixer;
    if (!mixer.init(48000, SDL_AUDIO_F32, 2)) return 1;

    // Map 1..5 to your files in assets/
    mixer.loadSound(1, "assets/sound.wav");
    mixer.loadSound(2, "assets/sound2.wav");
    mixer.loadSound(3, "assets/sound3.wav");
    mixer.loadSound(4, "assets/sound4.mp3"); // needs MP3 decoder in your SDL3_mixer build
    mixer.loadSound(5, "assets/sound5.mp3");

    std::cout <<
        "Commands:\n"
        "  1..5        -> play that sound (they overlay)\n"
        "  master=Y    -> set master volume (0..1)\n"
        "  tN=Y        -> set volume of last-created track index N (0..1)\n"
        "  q           -> quit\n";

    std::vector<MIX_Track*> tracks; // stash returned tracks so you can adjust volume
    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        if (line == "q" || line == "quit" || line == "exit") break;

        if (line.size() == 1 && line[0] >= '1' && line[0] <= '5') {
            int key = line[0] - '0';
            if (auto* t = mixer.play(key, 1.0f)) {
                tracks.push_back(t);
                std::cout << "(track #" << (int)tracks.size()-1 << " playing)\n";
            }
            continue;
        }
        if (line.rfind("master=",0)==0) {
            float v = std::stof(line.substr(7));
            mixer.setMasterVolume(v);
            std::cout << "master set\n";
            continue;
        }
        if (line.rfind("t",0)==0) { // tN=Y -> per-track gain
            auto eq = line.find('=');
            if (eq != std::string::npos) {
                int idx = std::stoi(line.substr(1, eq-1));
                float v  = std::stof(line.substr(eq+1));
                if (idx >= 0 && idx < (int)tracks.size() && tracks[idx]) {
                    mixer.setTrackVolume(tracks[idx], v);
                    std::cout << "track " << idx << " volume set\n";
                } else std::cout << "invalid track index\n";
            } else std::cout << "format: t0=0.5\n";
            continue;
        }

        std::cout << "unknown command. try 1..5, tN=Y, master=Y, q\n";
    }

    mixer.shutdown();
    return 0;
}
