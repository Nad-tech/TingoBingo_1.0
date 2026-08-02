//====================================================
// ProjectTree.cpp
//
// Generates a text file showing the folder structure
// of the current project.
//
// This utility demonstrates how to use
// std::filesystem to recursively traverse directories
// and produce a simple tree view.
//====================================================

// iostream provides std::cout for writing to the console.
#include <iostream>

// fstream provides file input and output.
#include <fstream>

// filesystem provides classes and functions for working
// with files and directories.
#include <filesystem>

// Create a shorter alias so we can write "fs::"
// instead of "std::filesystem::".
namespace fs = std::filesystem;

//===============================================================
// PrintTree
//
// Recursively writes the contents of a directory to the
// output file as a tree structure.
//
// Parameters:
//   path  - The directory currently being scanned.
//   out   - The output file.
//   depth - The current directory depth, used to indent
//           child files and folders.
//===============================================================
void PrintTree(const fs::path& path, std::ofstream& out, int depth = 0)
{
    // Visit every file and folder in the current directory.
    for (const auto& entry : fs::directory_iterator(path))
    {
        // Skip the Git repository metadata.
        if (entry.is_directory() && entry.path().filename() == ".git")
            continue;

        // Indent according to the current folder depth.
        for (int i = 0; i < depth; i++)
            out << "│   ";

        // Write the file or directory name.
        out << "├── " << entry.path().filename().string();

        // Add a trailing '/' to make directories easy to identify.
        if (entry.is_directory())
            out << "/";

        out << '\n';

        // Recursively process child directories.
        if (entry.is_directory())
        {
            PrintTree(entry.path(), out, depth + 1);
        }
    }
}

int main()
{
    // "." represents the current working directory.
    fs::path root = ".";

    // Create the output file.
    std::ofstream out("FileStructure.txt");

    // Stop if the file couldn't be created.
    if (!out)
    {
        std::cout << "Couldn't create output file.\n";
        return 1;
    }

    // Write the root folder name.
    out << root.string() << '\n';

    // Generate the directory tree.
    PrintTree(root, out);

    // Inform the user that the operation completed.
    std::cout << "Done! Wrote FileStructure.txt\n";

    return 0;
}