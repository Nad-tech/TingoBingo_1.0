//====================================================
// SpeechController.cpp
//
// Controls asynchronous speech generation and playback.
//
// Speech is generated on a background thread so the
// main game loop can continue updating and drawing.
// Once the WAV file is ready, it is loaded and played
// from the main thread.
//====================================================

#include "SpeechController.h"
#include "Speech.h"
#include "Input.h"

// Update speech generation and playback.
void SpeechController::Update()
{
    // Load and play the generated speech once the
    // worker thread has finished creating the WAV file.
    if (wavReady)
    {
        speech = LoadSound("assets/audio/voice/speech.wav");

        PlaySound(speech);

        wavReady = false;
        soundLoaded = true;
    }

    // Release the sound once playback has finished.
    if (soundLoaded && !IsSoundPlaying(speech))
    {
        UnloadSound(speech);

        speaking = false;
        soundLoaded = false;
    }
}

bool SpeechController::SoundLoaded()
{
    return soundLoaded;
}

// Returns true while speech is being generated
// or played.
bool SpeechController::IsSpeaking() const
{
    return speaking;
}

// Begin generating speech on a background thread.
void SpeechController::Speak(const std::string& text)
{
    // Ignore new speech requests while already speaking.
    if (speaking)
    {
        return;
    }

    speechThread = std::thread([this, text]()
    {
        speaking = true;

        // Generate the speech WAV file using Piper.
        Speech::Speak(text);

        // Notify the main thread that the WAV file
        // is ready to be loaded and played.
        wavReady = true;
    });

    // Allow the worker thread to continue independently.
    speechThread.detach();
}