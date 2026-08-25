#include "SpeechController.h"
#include "Speech.h"
#include <iostream>

void SpeechController::Update()
{
    if(wavReady)
    {
        std::cout << "WAV is ready\n";

        wavReady = false;

        speechSound = LoadSound("./assets/audio/voice/speech.wav");
        soundLoaded = true;

        PlaySound(speechSound);
        
        state = State::Playing;
    }

    if(state == State::Playing && !IsSoundPlaying(speechSound))
    {
        UnloadSound(speechSound);

        soundLoaded = false;
        state = State::Idle;
    }
}

void SpeechController::Speak(const std::string& text)
{
    if (state != State::Idle)
    {
        return;
    }

    if(speechThread.joinable())
    {
        speechThread.join();
    }

    state = State::Generating;

    speechThread = std::thread([this, text]()
    {
        std::cout << "Worker started\n";

        std::cout << "Before Speech::Speak()\n";

        bool success = Speech::Speak(text, stopRequested);

        std::cout << "After Speech::Speak()\n";

        if (success)
        {
            wavReady = true;
        }
        else
        {
            state = State::Idle;
        }
    });
}

SpeechController::~SpeechController()
{
    std::cout << "SpeechController destructor\n";

    stopRequested = true;

    if (speechThread.joinable())
    {
        std::cout << "Joining speech thread\n";

        speechThread.join();

        std::cout << "Speech thread joined\n";
    }
}