#pragma once

#include "raylib.h"

enum class AnimationPriority
{
    Idle,
    Emotion
};
class Animation
{
    public:
    Animation();

    void Initialise
    (
        int frameWidth,
        int frameHeight,
        int totalFrames,
        int columns,
        float frameDuration
    );

    void Update(float dt);

    Rectangle GetSourceRectangle() const;

    int GetFrameWidth() const;
    int GetFrameHeight() const;

    void SetFrame(int newFrame);
    int GetFrame() const;
    int GetTotalFrames() const;
    
    void Reset();

    void PreviousFrame();
    void NextFrame();
    
    void Play(int startFrame, int endFrame, AnimationPriority priority);
    bool IsPlaying() const;

    void Stop();

private:
    int frame;

    int frameWidth;
    int frameHeight;

    int totalFrames;
    int columns;

    float frameTimer;
    float frameDuration;

    bool playing;

    int startFrame;
    int endFrame;

    AnimationPriority priority;
};