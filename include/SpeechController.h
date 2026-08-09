#pragma once

#include <string>
#include <thread>
#include <atomic>
#include "raylib.h"

class SpeechController
{
public:
    void Update();
    void Speak(const std::string& text);
    bool IsSpeaking() const;
    bool SoundLoaded();

private:

    // True while speech is being generated or played.
    std::atomic<bool> speaking = false;

    // Background thread used to generate speech with Piper.
    std::thread speechThread;

    // Set by the worker thread when the WAV file is ready to play.
    std::atomic<bool> wavReady = false;

    // The currently loaded speech audio.
    Sound speech{};

    // True while the speech sound is loaded into memory.
    bool soundLoaded = false;
};