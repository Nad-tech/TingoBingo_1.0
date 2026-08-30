#pragma once

#include <string>
#include <atomic>

class Speech
{
public:
    static bool GenerateSpeech
    (
        const std::string& text,  
        const std::atomic<bool>& stopRequested
    );
};