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
    // directory_iterator loops through every file and folder
    // inside "path".
    for (const auto& entry : fs::directory_iterator(path))
    {
        //-------------------------------------------------------
        // Print indentation.
        //
        // If we're inside several folders, print
        // "│   " once for each level.
        //
        // Example:
        //
        // Root
        // │
        // ├── Folder
        // │   ├── File.txt
        //-------------------------------------------------------
        for (int i = 0; i < depth; i++)
            out << "│   ";

        //-------------------------------------------------------
        // Print the file or folder name.
        //
        // entry.path()
        //      Returns the complete path.
        //
        // filename()
        //      Extracts just the name.
        //
        // string()
        //      Converts it into a std::string.
        //-------------------------------------------------------
        out << "├── " << entry.path().filename().string();

        //-------------------------------------------------------
        // If this entry is a directory,
        // add a "/" after its name.
        //-------------------------------------------------------
        if (entry.is_directory())
            out << "/";

        // Move to the next line.
        out << '\n';

        //-------------------------------------------------------
        // If this entry is another folder,
        // call PrintTree AGAIN.
        //
        // This is called RECURSION.
        //
        // Example:
        //
        // Root
        // ├── Animals
        //
        // PrintTree("Root")
        //     finds Animals
        //
        // PrintTree("Animals")
        //     scans everything inside Animals
        //-------------------------------------------------------
        if (entry.is_directory())
        {
            // depth + 1 means the next level is indented
            // one extra step.
            PrintTree(entry.path(), out, depth + 1);
        }
    }
}

int main()
{
    //-----------------------------------------------------------
    // "." means "the current folder".
    //
    // If you run the program from:
    //
    // C:\Projects\Boids
    //
    // then "." refers to:
    //
    // C:\Projects\Boids
    //-----------------------------------------------------------
    fs::path root = ".";

    //-----------------------------------------------------------
    // Create an output file.
    //
    // If it doesn't exist,
    // it will be created.
    //
    // If it already exists,
    // it will be overwritten.
    //-----------------------------------------------------------
    std::ofstream out("FileStructure.txt");

    //-----------------------------------------------------------
    // Check that the file opened successfully.
    //
    // "!out" means "opening failed".
    //-----------------------------------------------------------
    if (!out)
    {
        std::cout << "Couldn't create output file.\n";
        return 1;      // Return an error code.
    }

    //-----------------------------------------------------------
    // Write the root folder name.
    //
    // root.string() converts the filesystem path
    // into ordinary text.
    //-----------------------------------------------------------
    out << root.string() << '\n';

    //-----------------------------------------------------------
    // Scan the directory tree.
    //
    // This one function call does all the work.
    //-----------------------------------------------------------
    PrintTree(root, out);

    //-----------------------------------------------------------
    // Tell the user we're finished.
    //-----------------------------------------------------------
    std::cout << "Done! Wrote FileStructure.txt\n";

    // Returning 0 means the program completed successfully.
    return 0;
}