//====================================================
// Animation.cpp
//
// Manages sprite sheet animations.
//
// The Animation class tracks the current frame,
// advances animations over time and calculates the
// correct source rectangle for rendering.
//====================================================

#include "Animation.h"

// Initialise the animation with default values.
Animation::Animation()
{
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

// Configure the animation using information from
// the sprite sheet.
void Animation::Initialise(
    int width,
    int height,
    int frames,
    int cols,
    float duration)
{
    frameWidth = width;
    frameHeight = height;

    totalFrames = frames;
    columns = cols;

    frameDuration = duration;

    // Reset the animation.
    frame = 0;
    frameTimer = 0.0f;
}

// Advance the animation based on elapsed time.
void Animation::Update(float dt)
{
    // Do nothing if the animation isn't currently playing.
    if (!playing)
        return;

    // Count the elapsed time since the last frame.
    frameTimer += dt;

    // Wait until enough time has passed.
    if (frameTimer < frameDuration)
        return;

    // Remove one frame's worth of elapsed time.
    // Keeping any leftover time prevents the animation
    // from slowing down if frame times vary.
    frameTimer -= frameDuration;

    // Advance to the next frame.
    frame++;

    // Stop once the animation reaches the end frame.
    if (frame > endFrame)
    {
        frame = startFrame;
        playing = false;
    }
}

// Return the source rectangle for the current frame
// within the sprite sheet.
Rectangle Animation::GetSourceRectangle() const
{
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

// Reset the animation to the first frame.
void Animation::Reset()
{
    frame = 0;
    frameTimer = 0.0f;
}

// Set the current animation frame.
void Animation::SetFrame(int newFrame)
{
    frame = newFrame % totalFrames;
}

// Move to the previous frame.
void Animation::PreviousFrame()
{
    frame--;

    // Wrap around to the last frame.
    if (frame < 0)
        frame = totalFrames - 1;
}

// Move to the next frame.
void Animation::NextFrame()
{
    // Wrap around to the first frame.
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

// Play a section of the sprite sheet once.
void Animation::Play(int start, int end)
{
    // Ignore the request if an animation is already playing.
    if (playing)
        return;

    startFrame = start;
    endFrame = end;

    // Start playback from the first frame.
    frame = startFrame;
    frameTimer = 0.0f;

    playing = true;
}

// Returns true while an animation is playing.
bool Animation::IsPlaying() const
{
    return playing;
}