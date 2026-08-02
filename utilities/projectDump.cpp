//====================================================
// ProjectDump.cpp
//
// Creates a text file containing the contents of all
// C++ source and header files in the project.
//
// This utility is useful for creating a single file
// that can be shared for code reviews or archived as
// a snapshot of the project.
//====================================================

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int main()
{
    // Create the output file.
    std::ofstream out("ProjectDump.txt");

    // Visit every file in the project directory.
    for (const auto& entry : fs::recursive_directory_iterator("."))
    {
        // Ignore directories.
        if (!entry.is_regular_file())
            continue;

        // Don't include the output file itself.
        if (entry.path().filename() == "ProjectDump.txt")
            continue;

        // Skip generated build files.
        if (entry.path().string().find("build") != std::string::npos)
            continue;

        std::string ext = entry.path().extension().string();

        // Only include C++ source and header files.
        if (ext == ".cpp" || ext == ".h")
        {
            // Write a heading for each file.
            out << "=====================================\n";
            out << entry.path().string() << "\n";
            out << "=====================================\n\n";

            std::ifstream in(entry.path());

            std::string line;

            // Copy the file into the output.
            while (std::getline(in, line))
            {
                out << line << '\n';
            }

            out << "\n\n";
        }
    }

    std::cout << "Finished!\n";

    return 0;
}