#pragma once

#include <string>
#include <atomic>
#include <thread>
#include "raylib.h"


//====================================================
// SpeechController
//
// Manages Tingo's speech generation and audio playback.
//
// Speech generation is performed on a worker thread
// using Piper/FFmpeg, while Raylib audio operations
// are handled on the main thread.
//
// Speech lifecycle:
//
//     Idle → Generating → Playing → Idle
//
// Generating = Piper/FFmpeg are creating the WAV file.
// Playing    = Raylib is playing the generated WAV.
// Idle       = No speech is currently active.
//====================================================

class SpeechController
{
public:

    //================================================
    // State
    //
    // Represents the current stage of the speech
    // lifecycle.
    //================================================

    enum class State
    {
        Idle,
        Generating,
        Playing
    };


    //================================================
    // Update
    //
    // Runs on the main thread.
    //
    // Checks whether the worker thread has generated
    // the WAV file and, if so, loads and plays it
    // through Raylib.
    //
    // Also detects when Raylib has finished playing
    // the speech.
    //================================================

    void Update();


    //================================================
    // Speak
    //
    // Starts a new speech request.
    //
    // Speech generation is performed on a worker
    // thread so Piper/FFmpeg do not block the
    // main game loop.
    //================================================

    void Speak(const std::string& text);


    //================================================
    // Destructor
    //
    // Requests the speech worker to stop and joins
    // the worker thread before the controller is
    // destroyed.
    //================================================

    ~SpeechController();


    //================================================
    // SoundLoaded
    //
    // Returns true when the generated speech WAV
    // is currently loaded into a Raylib Sound.
    //================================================

    bool SoundLoaded();


    //================================================
    // SpeechFinished
    //
    // Returns true when the complete speech lifecycle
    // has finished.
    //
    // This remains false while speech is generating
    // or playing, and becomes true once playback has
    // finished and the controller returns to Idle.
    //================================================

    bool SpeechFinished();


private:

    // Current stage of the speech lifecycle.
    State state = State::Idle;


    //================================================
    // Worker Thread Communication
    //================================================

    // Set by the main thread when shutdown has been
    // requested.
    //
    // The speech worker checks this flag while
    // generating speech and stops when requested.
    std::atomic<bool> stopRequested{false};


    // Set by the worker thread when Speech::Speak()
    // has successfully generated the WAV file.
    //
    // The main thread checks this flag in Update().
    std::atomic<bool> wavReady{false};


    // Worker thread responsible for speech generation.
    std::thread speechThread;


    //================================================
    // Raylib Audio
    //================================================

    // The generated speech audio loaded by Raylib.
    Sound speechSound{};


    // True while speechSound contains a loaded
    // Raylib Sound.
    bool soundLoaded = false;


    // Tracks whether the complete speech request has
    // finished.
    //
    // false = generating or playing
    // true  = speech has completely finished
    //
    // This is separate from SoundIsPlaying() because
    // speech can be not playing while it is still
    // being generated.
    bool speechFinished = true;
};