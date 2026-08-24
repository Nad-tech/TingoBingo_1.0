#pragma once

#include <string>
#include <atomic>

class Speech
{
public:
    static bool Speak
    (
        const std::string& text,  
        const std::atomic<bool>& stopRequested
    );
};