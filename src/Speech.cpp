//====================================================
// Speech.cpp
//
// Generates speech audio using Piper.
//
// Text is passed to the Piper command-line tool,
// which creates a WAV file that can later be played
// by the game.
//====================================================

#include "Speech.h"

#include <cstdlib>

// Convert text into a spoken WAV file using Piper.
void Speech::Speak(const std::string& text)
{
    // Build the command used to launch Piper.
    std::string command =
        "echo \"" + text + "\" | "
        "\"tools\\piper\\piper.exe\" "
        "--model \"tools\\piper\\en_GB-semaine-medium.onnx\" "
        "--length_scale 1.5 "
        "--noise_scale 1.3 "
        "--noise_w 0.9 "
        "--sentence_silence 0.03 "
        "--output_file \"assets\\audio\\voice\\speech.wav\"";

    // Execute the command and generate the speech file.
    system(command.c_str());
}