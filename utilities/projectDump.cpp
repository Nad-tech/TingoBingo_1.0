#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int main()
{
    std::ofstream out("ProjectDump.txt");

    for (const auto& entry : fs::recursive_directory_iterator("."))
    {
        if (!entry.is_regular_file())
            continue;

        if (entry.path().filename() == "ProjectDump.txt")
            continue;

        if (entry.path().string().find("build") != std::string::npos)
            continue;

        std::string ext = entry.path().extension().string();

        if (ext == ".cpp" || ext == ".h")
        {
            out << "=====================================\n";
            out << entry.path().string() << "\n";
            out << "=====================================\n\n";

            std::ifstream in(entry.path());

            std::string line;
            while (std::getline(in, line))
            {
                out << line << '\n';
            }

            out << "\n\n";
        }
    }

    std::cout << "Finished!\n";
}