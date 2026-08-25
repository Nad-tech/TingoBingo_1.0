#pragma once

#include <string>
#include <atomic>
#include <thread>
#include "raylib.h"
class SpeechController
{
public:
    enum class State
    {
        Idle,
        Generating,
        Playing
    };

    void Update();
    void Speak(const std::string& text);
    ~SpeechController();

private:
    State state = State::Idle;

    std::atomic<bool> stopRequested{false};
    std::atomic<bool> wavReady{false};

    std::thread speechThread;

    Sound speechSound{};
    bool soundLoaded = false; 
};