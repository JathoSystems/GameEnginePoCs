#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize SDL with audio subsystem
    if (!SDL_Init(SDL_INIT_AUDIO)) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load the WAV file
    SDL_AudioSpec wavSpec;
    Uint8* wavBuffer;
    Uint32 wavLength;
    
    if (!SDL_LoadWAV("../assets/sound.wav", &wavSpec, &wavBuffer, &wavLength)) {
        SDL_Log("Failed to load WAV file! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Open audio device
    SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
        &wavSpec,
        NULL,
        NULL
    );

    if (!stream) {
        SDL_Log("Failed to open audio device! SDL_Error: %s\n", SDL_GetError());
        SDL_free(wavBuffer);
        SDL_Quit();
        return 1;
    }

    // Put the audio data into the stream
    SDL_PutAudioStreamData(stream, wavBuffer, wavLength);
    
    // Flush and resume playback
    SDL_FlushAudioStream(stream);
    SDL_ResumeAudioStreamDevice(stream);

    std::cout << "Playing sound... Press Enter to exit." << std::endl;

    // Wait for user input to keep the program running
    std::cin.get();

    // Cleanup
    SDL_DestroyAudioStream(stream);
    SDL_free(wavBuffer);
    SDL_Quit();

    std::cout << "Sound finished, exiting..." << std::endl;

    return 0;
}