#pragma once

#include "raylib.h"


//====================================================
// AnimationPriority
//
// Determines which animations are allowed to control
// the Animation object when another animation is
// already playing.
//
// Idle animations are low priority and can be
// interrupted by higher-priority animations such as
// emotions.
//====================================================

enum class AnimationPriority
{
    Idle,
    Emotion
};


//====================================================
// Animation
//
// Controls sprite-sheet animation.
//
// Animation tracks the current frame, timing,
// animation range and playback state.
//
// Individual sprites such as the eyes and mouth use
// this class to control their own animations.
//====================================================

class Animation
{
public:

    // Create an animation with its default state.
    Animation();


    //================================================
    // Initialisation
    //================================================

    // Configure the animation using the dimensions
    // and layout of the sprite sheet.
    void Initialise
    (
        int frameWidth,
        int frameHeight,
        int totalFrames,
        int columns,
        float frameDuration
    );


    //================================================
    // Playback
    //================================================

    // Advance the animation based on elapsed time.
    void Update(float dt);

    // Return the source rectangle for the current
    // frame of the sprite sheet.
    Rectangle GetSourceRectangle() const;


    // Return the dimensions of an individual frame.
    int GetFrameWidth() const;
    int GetFrameHeight() const;


    //================================================
    // Frame Control
    //================================================

    // Set the current animation frame directly.
    void SetFrame(int newFrame);

    // Return the current animation frame.
    int GetFrame() const;

    // Return the total number of frames in the
    // sprite sheet.
    int GetTotalFrames() const;

    // Reset the animation back to its initial state.
    void Reset();

    // Move one frame backwards or forwards.
    void PreviousFrame();
    void NextFrame();


    //================================================
    // Animation Sequences
    //================================================

    // Play a range of frames using the supplied
    // animation priority.
    //
    // Higher-priority animations can interrupt
    // lower-priority animations.
    void Play(
        int startFrame,
        int endFrame,
        AnimationPriority priority
    );

    // Return true while an animation sequence is playing.
    bool IsPlaying() const;

    // Stop the current animation.
    void Stop();


private:

    // Current frame being displayed.
    int frame;


    // Dimensions of an individual sprite frame.
    int frameWidth;
    int frameHeight;


    // Total number of frames in the sprite sheet
    // and number of columns used by the sheet.
    int totalFrames;
    int columns;


    // Tracks elapsed time for the current frame.
    // frameDuration determines how long each frame
    // remains visible.
    float frameTimer;
    float frameDuration;


    // True while an animation sequence is active.
    bool playing;


    // First and last frames of the current animation
    // sequence.
    int startFrame;
    int endFrame;


    // Priority of the animation currently controlling
    // this Animation object.
    AnimationPriority priority;
};