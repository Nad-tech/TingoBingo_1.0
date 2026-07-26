// iostream gives us std::cout for printing to the console.
#include <iostream>

// fstream lets us create and write to files.
#include <fstream>

// filesystem provides tools for working with files and folders.
#include <filesystem>

// Create a shorter name.
// Instead of writing std::filesystem everywhere,
// we can just write fs.
namespace fs = std::filesystem;

//---------------------------------------------------------------
// PrintTree
//
// Recursively prints the contents of a folder.
//
// Parameters:
//
// path  - The folder we are currently scanning.
// out   - The output file we are writing to.
// depth - How deep we are in the folder structure.
//         Used only to indent the output nicely.
//---------------------------------------------------------------
void PrintTree(const fs::path& path, std::ofstream& out, int depth = 0)
{
    for (const auto& entry : fs::directory_iterator(path))
    {
        // Skip the .git directory completely.
        if (entry.is_directory() && entry.path().filename() == ".git")
            continue;

        //-------------------------------------------------------
        // Print indentation.
        //-------------------------------------------------------
        for (int i = 0; i < depth; i++)
            out << "│   ";

        //-------------------------------------------------------
        // Print the file or folder name.
        //-------------------------------------------------------
        out << "├── " << entry.path().filename().string();

        //-------------------------------------------------------
        // Add "/" after directories.
        //-------------------------------------------------------
        if (entry.is_directory())
            out << "/";

        out << '\n';

        //-------------------------------------------------------
        // Recurse into subdirectories.
        //-------------------------------------------------------
        if (entry.is_directory())
        {
            PrintTree(entry.path(), out, depth + 1);
        }
    }
}

int main()
{
    //-----------------------------------------------------------
    // "." means "the current folder".
    //-----------------------------------------------------------
    fs::path root = ".";

    //-----------------------------------------------------------
    // Create an output file.
    //-----------------------------------------------------------
    std::ofstream out("FileStructure.txt");

    //-----------------------------------------------------------
    // Check that the file opened successfully.
    //-----------------------------------------------------------
    if (!out)
    {
        std::cout << "Couldn't create output file.\n";
        return 1;
    }

    //-----------------------------------------------------------
    // Write the root folder name.
    //-----------------------------------------------------------
    out << root.string() << '\n';

    //-----------------------------------------------------------
    // Scan the directory tree.
    //-----------------------------------------------------------
    PrintTree(root, out);

    //-----------------------------------------------------------
    // Tell the user we're finished.
    //-----------------------------------------------------------
    std::cout << "Done! Wrote FileStructure.txt\n";

    return 0;
}