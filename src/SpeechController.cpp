//====================================================
// SpeechController.cpp
//
// Controls asynchronous speech generation and playback.
//
// Speech is generated on a background thread so the
// main game loop can continue updating and drawing.
//
// Once the WAV file is ready, it is loaded and played
// from the main thread.
//
// SpeechController also owns the speech worker thread
// and makes sure it is safely joined when it is finished
// or when the controller is destroyed.
//====================================================

#include "SpeechController.h"
#include "Speech.h"
#include "Input.h"


//====================================================
// Update
//
// Runs on the main game thread.
//
// Handles two stages of speech:
//
// 1. Loading and starting playback once the worker
//    has finished generating the WAV.
//
// 2. Unloading the sound once playback has finished.
//====================================================

void SpeechController::Update()
{
    //================================================
    // SPEECH READY
    //================================================

    // The worker thread sets wavReady to true when
    // Piper and FFmpeg have successfully generated
    // the final speech.wav file.
    //
    // Sound loading and playback happen on the main
    // thread because Raylib audio functions should be
    // handled by the main game thread.
    if (wavReady)
    {
        // Load the generated WAV file into Raylib.
        speech = LoadSound(
            "assets/audio/voice/speech.wav"
        );

        // Begin playing the generated speech.
        PlaySound(speech);

        // The WAV has now been consumed by the main
        // thread, so clear the ready flag.
        wavReady = false;

        // Remember that the Raylib Sound is currently
        // loaded and being used for playback.
        soundLoaded = true;
    }


    //================================================
    // SPEECH FINISHED
    //================================================

    // Once the sound has finished playing, release
    // the Raylib audio resource.
    if (soundLoaded && !IsSoundPlaying(speech))
    {
        // Free the sound from memory.
        UnloadSound(speech);

        // Speech is now completely finished.
        //
        // speaking stays true while Piper/FFmpeg are
        // generating the WAV and while the audio is
        // playing. It becomes false only after the
        // actual audio playback has finished.
        speaking = false;

        // The Sound is no longer loaded.
        soundLoaded = false;
    }
}


//====================================================
// SoundLoaded
//
// Returns true when the generated speech sound has
// been loaded into Raylib and playback has started.
//====================================================

bool SpeechController::SoundLoaded()
{
    return soundLoaded;
}


//====================================================
// IsSpeaking
//
// Returns true while speech is somewhere in its
// lifecycle:
//
//     Generating → Playing → Finished
//
// The flag is therefore used by RobotBrain to know
// whether the speech request is still active.
//====================================================

bool SpeechController::IsSpeaking() const
{
    return speaking;
}


//====================================================
// Speak
//
// Starts asynchronous speech generation.
//
// The expensive Piper and FFmpeg work is performed
// on a background thread so the main Raylib game loop
// does not freeze while speech is being generated.
//====================================================

void SpeechController::Speak(const std::string& text)
{
    //================================================
    // PREVENT OVERLAPPING SPEECH
    //================================================

    // Ignore a new speech request if Tingo is already
    // generating or playing speech.
    if (speaking)
    {
        return;
    }


    //================================================
    // CLEAN UP PREVIOUS WORKER
    //================================================

    // A std::thread remains "joinable" even after its
    // function has finished executing.
    //
    // Join the previous worker before reusing the
    // std::thread object.
    if (speechThread.joinable())
    {
        speechThread.join();
    }


    //================================================
    // START NEW SPEECH
    //================================================

    // Mark speech as active BEFORE starting the worker.
    //
    // This is important because it prevents the main
    // thread from seeing "not speaking" during the tiny
    // period before the worker thread starts executing.
    speaking = true;

    // A new speech request does not have a WAV ready yet.
    wavReady = false;


    // Create the background worker thread.
    speechThread = std::thread([this, text]()
    {
        // Generate the speech WAV using Piper and FFmpeg.
        //
        // stopRequested allows Speech::Speak() to
        // terminate the external processes if the
        // application is shutting down.
        bool success = Speech::Speak(
            text,
            stopRequested
        );


        //================================================
        // SPEECH GENERATION RESULT
        //================================================

        // If Piper and FFmpeg succeeded, notify the
        // main thread that speech.wav is ready.
        if (success)
        {
            wavReady = true;
        }
        else
        {
            // Generation failed or shutdown was requested.
            //
            // There will be no WAV for the main thread
            // to play, so mark the speech request as finished.
            speaking = false;
        }
    });
}


//====================================================
// Destructor
//
// Safely shuts down the speech worker.
//
// The worker may still be inside Piper or FFmpeg when
// the application is closing.
//
// stopRequested tells Speech::Speak() to terminate
// the external process it is currently monitoring.
//
// join() then waits for the worker to completely exit
// before SpeechController itself is destroyed.
//====================================================

SpeechController::~SpeechController()
{
    // Tell the speech worker that the application is
    // shutting down.
    stopRequested = true;


    // If the worker is still running, wait for it to
    // finish before destroying SpeechController.
    //
    // This prevents the worker from continuing to access
    // SpeechController after the object has been destroyed.
    if (speechThread.joinable())
    {
        speechThread.join();
    }
}