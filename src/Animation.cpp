#include "Animation.h"

Animation::Animation()
{
    // Default animation state
    frame = 0;

    frameWidth = 0;
    frameHeight = 0;

    totalFrames = 1;
    columns = 1;

    frameTimer = 0.0f;
    frameDuration = 0.1f;

    playing = false;

    startFrame = 0;
    endFrame = 0;
}

void Animation::Initialise(
    int width,
    int height,
    int frames,
    int cols,
    float duration)
{
    // Store animation properties
    frameWidth = width;
    frameHeight = height;

    totalFrames = frames;
    columns = cols;

    frameDuration = duration;

    // Reset animation
    frame = 0;
    frameTimer = 0.0f;
}

void Animation::Update(float dt)
{
    // Do nothing if animation isn't playing
    if (!playing)
        return;

    // Count elapsed time
    frameTimer += dt;

    // Wait until it's time for the next frame
    if (frameTimer < frameDuration)
        return;
    /*
    Remove one frame's worth of elapsed time
    Keep any leftover time for the next update
    Example: 0.18s - 0.10s = 0.08s carries into the next frame.
    Remove one frame's worth of time so any extra carries over.
    Example: 0.18s - 0.10s = 0.08s, keeping the animation accurate.
    By "keeping the animation accurate," I mean making sure it plays 
    at the correct speed over time, even if your game's frame rate isn't 
    perfectly consistent.
    frameTimer -= frameDuration;
    */

    frameTimer -= frameDuration;

    // Advance to the next frame
    frame++;

    // Stop after the last frame
    if (frame > endFrame)
    {
        frame = startFrame;
        playing = false;
    }
}

Rectangle Animation::GetSourceRectangle() const
{
    // Calculate sprite sheet position
    int column = frame % columns;
    int row = frame / columns;

    return
    {
        (float)(column * frameWidth),
        (float)(row * frameHeight),
        (float)frameWidth,
        (float)frameHeight
    };
}

void Animation::Reset()
{
    // Return to the first frame
    frame = 0;
    frameTimer = 0.0f;
}

void Animation::SetFrame(int newFrame)
{
    // Set a specific frame
    frame = newFrame % totalFrames;
}

void Animation::PreviousFrame()
{
    // Move back one frame
    frame--;

    if (frame < 0)
        frame = totalFrames - 1;
}

void Animation::NextFrame()
{
    // Move forward one frame
    frame = (frame + 1) % totalFrames;
}

int Animation::GetFrameWidth() const
{
    return frameWidth;
}

int Animation::GetFrameHeight() const
{
    return frameHeight;
}

int Animation::GetFrame() const
{
    return frame;
}

int Animation::GetTotalFrames() const
{
    return totalFrames;
}

void Animation::Play(int start, int end)
{
    // Ignore if already playing
    if (playing)
        return;

    // Set playback range
    startFrame = start;
    endFrame = end;

    // Start at the first frame
    frame = startFrame;
    frameTimer = 0.0f;

    playing = true;
}

bool Animation::IsPlaying() const
{
    return playing;
}