#include "SpeechController.h"
#include "Speech.h"
#include <iostream>


//====================================================
// Update
//
// Runs on the main thread.
//
// Handles communication between the speech worker
// thread and the Raylib audio system.
//
// The worker thread is responsible for generating
// the WAV file.
//
// The main thread is responsible for loading and
// playing the WAV through Raylib.
//
// Speech lifecycle:
//
//     Generating → Playing → Idle
//
// speechFinished remains false while speech is
// generating or playing, and becomes true when
// playback has completely finished.
//====================================================

void SpeechController::Update()
{
    //================================================
    // WAV READY
    //
    // The worker thread sets wavReady to true when
    // Speech::Speak() has successfully generated
    // the WAV file.
    //
    // Because wavReady is atomic, it can safely be
    // written by the worker thread and read by the
    // main thread.
    //================================================

    if(wavReady)
    {
        std::cout << "WAV is ready\n";


        // Reset the flag so the same WAV is not
        // loaded and played again on the next frame.
        wavReady = false;


        // Load the generated WAV into a Raylib Sound.
        //
        // Raylib audio operations are performed on
        // the main thread rather than the worker thread.
        speechSound =
            LoadSound("./assets/audio/voice/speech.wav");

        soundLoaded = true;


        // Start playing the generated speech.
        PlaySound(speechSound);


        // Speech generation is complete and the
        // generated audio has now started playing.
        state = State::Playing;


        // The complete speech request is not finished
        // yet because the sound is currently playing.
        speechFinished = false;
    }


    //================================================
    // PLAYBACK FINISHED
    //
    // Check whether speech is currently playing
    // and Raylib has finished the sound.
    //
    // IsSoundPlaying() returns false once playback
    // has completed.
    //
    // IsSoundPlaying() is a Raylib function that checks
    // whether the Sound is currently being played.
    //================================================

    if(state == State::Playing &&
       !IsSoundPlaying(speechSound))
    {
        std::cout << "PLAYBACK FINISHED\n";


        // The audio has finished playing, so the
        // Raylib Sound resource can now be released.
        UnloadSound(speechSound);


        // Keep track of the fact that there is no
        // longer a loaded speech sound.
        soundLoaded = false;


        // The complete speech lifecycle has finished.
        //
        // Returning to Idle allows the controller to
        // accept another speech request.
        state = State::Idle;


        // Tell the RobotBrain that the entire speech
        // request has now finished.
        speechFinished = true;
    }
}


//====================================================
// Speak
//
// Starts a new speech request.
//
// Speech generation is performed on a worker thread
// so Piper and FFmpeg do not block the main game loop.
//
// The controller moves into the Generating state
// immediately while the worker creates the WAV file.
//====================================================

void SpeechController::Speak(const std::string& text)
{
    //================================================
    // CHECK WHETHER SPEECH CAN START
    //
    // A new speech request can only begin when the
    // controller is Idle.
    //
    // This prevents another worker thread from being
    // created while speech is already generating or
    // playing.
    //================================================

    if (state != State::Idle)
    {
        return;
    }


    //================================================
    // JOIN PREVIOUS WORKER
    //
    // A std::thread remains joinable even after the
    // function running on it has finished.
    //
    // Join the previous worker before reusing the
    // speechThread object.
    //================================================

    if(speechThread.joinable())
    {
        // Wait for the previous worker to finish and
        // safely join it with the main thread.
        speechThread.join();
    }


    //================================================
    // START GENERATION
    //================================================

    // Tell the controller that speech generation is
    // now in progress.
    //
    // This prevents another Speak() request from
    // starting while the current request is active.
    state = State::Generating;


    // The speech request has started, so it cannot be
    // considered finished while the WAV is generating.
    speechFinished = false;


    //================================================
    // CREATE WORKER THREAD
    //================================================

    // Create and start the worker thread.
    //
    // The lambda contains the code executed by the
    // worker thread.
    //
    // [this, text] means:
    //
    // this
    //     Gives the lambda access to this
    //     SpeechController object.
    //
    // text
    //     Makes a copy of the speech text so the
    //     worker has its own copy to use.
    speechThread = std::thread([this, text]()
    {
        std::cout << "Worker started\n";

        std::cout << "Before Speech::Speak()\n";


        //================================================
        // GENERATE SPEECH
        //
        // Speech::Speak() runs Piper and FFmpeg on
        // the worker thread.
        //
        // stopRequested is shared between the main
        // thread and worker thread and allows the
        // generation process to be cancelled.
        //================================================

        bool success =
            Speech::Speak(text, stopRequested);


        std::cout << "After Speech::Speak()\n";


        //================================================
        // GENERATION RESULT
        //================================================

        if (success)
        {
            // The WAV has successfully been generated.
            //
            // Tell the main thread that it can now
            // load and play the WAV.
            wavReady = true;
        }
        else
        {
            // Speech generation failed or was cancelled.
            //
            // No audio will be played, so return the
            // controller to the Idle state.
            state = State::Idle;
        }
    });
}


//====================================================
// Destructor
//
// Called when SpeechController is destroyed.
//
// Ensures the speech worker is safely stopped and
// joined before the SpeechController object disappears.
//====================================================

SpeechController::~SpeechController()
{
    std::cout << "SpeechController destructor\n";


    //================================================
    // REQUEST WORKER SHUTDOWN
    //================================================

    // Tell Speech::Speak() that shutdown has been
    // requested.
    //
    // Speech::Speak() periodically checks this flag
    // while Piper and FFmpeg are running.
    stopRequested = true;


    //================================================
    // JOIN WORKER
    //================================================

    // Check whether the worker thread still needs
    // to be joined.
    if (speechThread.joinable())
    {
        std::cout << "Joining speech thread\n";


        // Wait for the worker to finish before
        // destroying the SpeechController.
        //
        // This prevents the worker from accessing
        // the controller after it has been destroyed.
        speechThread.join();


        std::cout << "Speech thread joined\n";
    }
}


//====================================================
// SoundLoaded
//
// Returns true while the generated speech WAV is
// currently loaded as a Raylib Sound.
//====================================================

bool SpeechController::SoundLoaded()
{
    return soundLoaded;
}


//====================================================
// SpeechFinished
//
// Returns true when the complete speech lifecycle
// has finished.
//
// false:
//     Speech is generating or playing.
//
// true:
//     Playback has finished and the controller
//     has returned to Idle.
//
// This is deliberately separate from checking whether
// the sound is playing because speech can be temporarily
// "not playing" while the WAV is still being generated.
//====================================================

bool SpeechController::SpeechFinished()
{
    return speechFinished;
}