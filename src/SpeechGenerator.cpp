//====================================================
// Speech.cpp
//
// Generates speech audio using Piper and FFmpeg.
//
// Piper receives text through a Windows stdin pipe.
// This avoids shell execution and means special
// characters in the spoken text are not interpreted
// by the command shell.
//
// Piper creates speech_raw.wav.
//
// FFmpeg then applies the selected audio effects
// and creates the final speech.wav.
//
// All project paths are relative to the application's
// current working directory, so the project does not
// depend on a specific developer's machine path.
//====================================================

#include "SpeechGenerator.h"

#include <filesystem>
#include <iostream>

#include "windows.h"


//====================================================
// Helper: CloseProcessHandles
//
// Safely closes the handles returned by
// CreateProcessA().
//
// The process itself has already finished or has
// been terminated before this function is called.
//====================================================

static void CloseProcessHandles(PROCESS_INFORMATION& process)
{
    if (process.hProcess)
    {
        CloseHandle(process.hProcess);
        process.hProcess = nullptr;
    }

    if (process.hThread)
    {
        CloseHandle(process.hThread);
        process.hThread = nullptr;
    }
}


//====================================================
// Speak
//
// Generates a processed speech WAV file.
//
// Returns:
//
//     true  - Piper and FFmpeg succeeded.
//
//     false - Something failed or shutdown was
//             requested.
//====================================================

bool Speech::GenerateSpeech
(
    const std::string& text,
    const std::atomic<bool>& stopRequested
)
{
    //================================================
    // PROJECT PATHS
    //================================================

    // Use the application's current working directory
    // as the project root.
    //
    // This replaces paths such as:
    //
    // Example of the old machine-specific path:
    // C:/dev/raylib-projects/TingoBingo_1.0/
    //
    // with paths relative to the project.
    const std::filesystem::path projectRoot =
        std::filesystem::current_path();

    const std::filesystem::path piperPath =
        projectRoot /
        "tools" /
        "piper" /
        "piper.exe";

    const std::filesystem::path piperModelPath =
        projectRoot /
        "tools" /
        "piper" /
        "en_GB-alan-medium.onnx";

    const std::filesystem::path ffmpegPath =
        projectRoot /
        "tools" /
        "ffmpeg" /
        "bin" /
        "ffmpeg.exe";

    const std::filesystem::path rawSpeechPath =
        projectRoot /
        "assets" /
        "audio" /
        "voice" /
        "speech_raw.wav";

    const std::filesystem::path speechPath =
        projectRoot /
        "assets" /
        "audio" /
        "voice" /
        "speech.wav";


    //================================================
    // VERIFY REQUIRED FILES
    //================================================

    // Check that Piper exists before trying to launch it.
    if (!std::filesystem::exists(piperPath))
    {
        std::cout
            << "Piper executable not found: "
            << piperPath.string()
            << "\n";

        return false;
    }


    // Check that the Piper voice model exists.
    if (!std::filesystem::exists(piperModelPath))
    {
        std::cout
            << "Piper model not found: "
            << piperModelPath.string()
            << "\n";

        return false;
    }


    // Check that FFmpeg exists.
    if (!std::filesystem::exists(ffmpegPath))
    {
        std::cout
            << "FFmpeg executable not found: "
            << ffmpegPath.string()
            << "\n";

        return false;
    }


    //================================================
    // PIPER INPUT PIPE
    //================================================

    // Create a Windows pipe that will become Piper's
    // standard input.
    //
    // Our program writes text into:
    //
    //     piperStdInWrite
    //
    // Piper reads that text from:
    //
    //     piperStdInRead
    SECURITY_ATTRIBUTES securityAttributes{};

    securityAttributes.nLength =
        sizeof(securityAttributes);

    securityAttributes.bInheritHandle = TRUE;

    securityAttributes.lpSecurityDescriptor =
        nullptr;


    HANDLE piperStdInRead = nullptr;
    HANDLE piperStdInWrite = nullptr;


    if (!CreatePipe(
            &piperStdInRead,
            &piperStdInWrite,
            &securityAttributes,
            0))
    {
        std::cout
            << "Failed to create Piper stdin pipe. Error: "
            << GetLastError()
            << "\n";

        return false;
    }


    // The parent process needs the write handle,
    // but Piper only needs the read handle.
    //
    // Prevent Piper from inheriting the write handle.
    //
    // This is important because otherwise Piper could
    // keep its own copy of the write side open.
    if (!SetHandleInformation(
            piperStdInWrite,
            HANDLE_FLAG_INHERIT,
            0))
    {
        std::cout
            << "Failed to configure Piper stdin pipe. Error: "
            << GetLastError()
            << "\n";

        CloseHandle(piperStdInRead);
        CloseHandle(piperStdInWrite);

        return false;
    }


    //================================================
    // START PIPER
    //================================================

    STARTUPINFOA piperStartupInfo{};
    PROCESS_INFORMATION piperProcess{};

    piperStartupInfo.cb =
        sizeof(piperStartupInfo);


    // Tell Windows that Piper should use the handles
    // supplied below for standard input/output/error.
    piperStartupInfo.dwFlags |=
        STARTF_USESTDHANDLES;


    // Piper reads its text from our pipe.
    piperStartupInfo.hStdInput =
        piperStdInRead;


    // Keep Piper's output/error behaviour normal.
    piperStartupInfo.hStdOutput =
        GetStdHandle(STD_OUTPUT_HANDLE);

    piperStartupInfo.hStdError =
        GetStdHandle(STD_ERROR_HANDLE);


    // Build Piper's command line.
    //
    // Notice that the user's text is NOT part of this
    // command line.
    //
    // That means characters such as:
    //
    //     "
    //     &
    //     |
    //     <
    //     >
    //
    // cannot be interpreted as shell commands.
    //
    // The text will be sent through stdin instead.
    std::string piperCommand =
        "\"" + piperPath.string() + "\" "
        "--model \"" + piperModelPath.string() + "\" "
        "--output_file \"" + rawSpeechPath.string() + "\"";


    // CreateProcessA() may modify the command-line
    // buffer, so commandLine must be a mutable string.
    if (!CreateProcessA(
            nullptr,
            piperCommand.data(),
            nullptr,
            nullptr,
            TRUE,
            CREATE_NO_WINDOW,
            nullptr,
            projectRoot.string().c_str(),
            &piperStartupInfo,
            &piperProcess))
    {
        std::cout
            << "Failed to launch Piper. Error: "
            << GetLastError()
            << "\n";

        CloseHandle(piperStdInRead);
        CloseHandle(piperStdInWrite);

        return false;
    }


    // Piper now owns the read side of the pipe.
    // The parent no longer needs it.
    CloseHandle(piperStdInRead);
    piperStdInRead = nullptr;


    //================================================
    // SEND TEXT TO PIPER
    //================================================

    // Add a newline so Piper receives the text as a
    // complete line, equivalent to the old:
    //
    // echo "text"
    //
    // approach.
    std::string input =
        text + "\n";


    DWORD bytesWritten = 0;


    if (!WriteFile(
            piperStdInWrite,
            input.c_str(),
            static_cast<DWORD>(input.size()),
            &bytesWritten,
            nullptr))
    {
        std::cout
            << "Failed to send text to Piper. Error: "
            << GetLastError()
            << "\n";

        CloseHandle(piperStdInWrite);
        piperStdInWrite = nullptr;

        TerminateProcess(
            piperProcess.hProcess,
            1
        );

        CloseProcessHandles(piperProcess);

        return false;
    }


    // Make sure the entire input was written.
    if (bytesWritten != input.size())
    {
        std::cout
            << "Piper stdin write was incomplete.\n";

        CloseHandle(piperStdInWrite);
        piperStdInWrite = nullptr;

        TerminateProcess(
            piperProcess.hProcess,
            1
        );

        CloseProcessHandles(piperProcess);

        return false;
    }


    // Closing the write side tells Piper:
    //
    // "There is no more input."
    //
    // Piper can now finish processing the text.
    CloseHandle(piperStdInWrite);
    piperStdInWrite = nullptr;


    //================================================
    // WAIT FOR PIPER
    //================================================

    // Don't use INFINITE here.
    //
    // Instead, check every 50 ms so the worker can
    // respond to a shutdown request.
    DWORD waitResult =
        WAIT_TIMEOUT;


    while (waitResult == WAIT_TIMEOUT)
    {
        if (stopRequested)
        {
            TerminateProcess(
                piperProcess.hProcess,
                1
            );

            CloseProcessHandles(piperProcess);

            return false;
        }


        waitResult =
            WaitForSingleObject(
                piperProcess.hProcess,
                50
            );
    }


    // If Windows reported a wait error, treat it as
    // a failed speech generation.
    if (waitResult != WAIT_OBJECT_0)
    {
        std::cout
            << "Failed while waiting for Piper. Error: "
            << GetLastError()
            << "\n";

        CloseProcessHandles(piperProcess);

        return false;
    }


    //================================================
    // CHECK PIPER RESULT
    //================================================

    DWORD piperExitCode = 0;

    if (!GetExitCodeProcess(
            piperProcess.hProcess,
            &piperExitCode))
    {
        std::cout
            << "Failed to get Piper exit code. Error: "
            << GetLastError()
            << "\n";

        CloseProcessHandles(piperProcess);

        return false;
    }


    if (piperExitCode != 0)
    {
        std::cout
            << "Piper failed. Exit code: "
            << piperExitCode
            << "\n";

        CloseProcessHandles(piperProcess);

        return false;
    }


    // Piper succeeded.
    CloseProcessHandles(piperProcess);


    //================================================
    // VERIFY PIPER OUTPUT
    //================================================

    // Make sure Piper actually created the WAV file
    // before asking FFmpeg to process it.
    if (!std::filesystem::exists(rawSpeechPath))
    {
        std::cout
            << "Piper completed but did not create: "
            << rawSpeechPath.string()
            << "\n";

        return false;
    }


    //================================================
    // START FFMPEG
    //================================================

    STARTUPINFOA ffmpegStartupInfo{};
    PROCESS_INFORMATION ffmpegProcess{};

    ffmpegStartupInfo.cb =
        sizeof(ffmpegStartupInfo);


    // Build the FFmpeg command line using paths relative
    // to the project location.
    //
    // No machine-specific C:\dev\... paths remain.
    std::string ffmpegCommand =
        "\"" + ffmpegPath.string() + "\" "
        "-y "
        "-i \"" + rawSpeechPath.string() + "\" "
        "-af \"aecho=0.8:0.88:60:0.25,"
        "highpass=f=250,"
        "lowpass=f=3500,"
        "acrusher=bits=12:mix=0.15\" "
        "\"" + speechPath.string() + "\"";


    if (!CreateProcessA(
            nullptr,
            ffmpegCommand.data(),
            nullptr,
            nullptr,
            FALSE,
            CREATE_NO_WINDOW,
            nullptr,
            projectRoot.string().c_str(),
            &ffmpegStartupInfo,
            &ffmpegProcess))
    {
        std::cout
            << "Failed to launch FFmpeg. Error: "
            << GetLastError()
            << "\n";

        return false;
    }


    //================================================
    // WAIT FOR FFMPEG
    //================================================

    waitResult =
        WAIT_TIMEOUT;


    while (waitResult == WAIT_TIMEOUT)
    {
        if (stopRequested)
        {
            TerminateProcess(
                ffmpegProcess.hProcess,
                1
            );

            CloseProcessHandles(ffmpegProcess);

            return false;
        }


        waitResult =
            WaitForSingleObject(
                ffmpegProcess.hProcess,
                50
            );
    }


    if (waitResult != WAIT_OBJECT_0)
    {
        std::cout
            << "Failed while waiting for FFmpeg. Error: "
            << GetLastError()
            << "\n";

        CloseProcessHandles(ffmpegProcess);

        return false;
    }


    //================================================
    // CHECK FFMPEG RESULT
    //================================================

    DWORD ffmpegExitCode = 0;

    if (!GetExitCodeProcess(
            ffmpegProcess.hProcess,
            &ffmpegExitCode))
    {
        std::cout
            << "Failed to get FFmpeg exit code. Error: "
            << GetLastError()
            << "\n";

        CloseProcessHandles(ffmpegProcess);

        return false;
    }


    if (ffmpegExitCode != 0)
    {
        std::cout
            << "FFmpeg failed. Exit code: "
            << ffmpegExitCode
            << "\n";

        CloseProcessHandles(ffmpegProcess);

        return false;
    }


    // FFmpeg succeeded.
    CloseProcessHandles(ffmpegProcess);


    //================================================
    // VERIFY FINAL OUTPUT
    //================================================

    // Make sure the final processed WAV actually exists
    // before telling SpeechController that it is ready.
    if (!std::filesystem::exists(speechPath))
    {
        std::cout
            << "FFmpeg completed but did not create: "
            << speechPath.string()
            << "\n";

        return false;
    }


    //================================================
    // SUCCESS
    //================================================


    return true;
}