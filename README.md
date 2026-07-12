# Using This Template

There are two ways to create a new project from this template.

---

## Option 1 – Copy the Template Folder

1. Copy the **Template** folder.

2. Rename the folder to your new project name.

3. Delete the existing `.git` folder.

4. Open a terminal in the project root.

5. Initialise a new Git repository:

   ```bash
   git init
   ```

6. Create a new repository on GitHub.

7. Connect your local repository to GitHub:

   ```bash
   git remote add origin <repository-url>
   ```

8. Stage all files:

   ```bash
   git add .
   ```

9. Create the initial commit:

   ```bash
   git commit -m "Initial commit"
   ```

10. Push the project to GitHub:

    ```bash
    git branch -M main
    git push -u origin main
    ```

11. Open `include/Constants.h` and change:

    * `WINDOW_TITLE`

12. Open `scripts/build.sh` and change:

    * `EXE_NAME`

Your new project is now ready for development.

---

## Option 2 – Use GitHub's Template Feature (Recommended)

If this repository has been marked as a **GitHub Template Repository**, you can avoid copying folders and deleting `.git`.

1. Open the Template repository on GitHub.

2. Click **Use this template**.

3. Enter a name for your new project.

4. Create the new repository.

5. Clone the new repository:

   ```bash
   git clone <repository-url>
   ```

6. Update the following project settings:

   * `WINDOW_TITLE` in `include/Constants.h`
   * `EXE_NAME` in `scripts/build.sh`

Your new project is now ready for development.

---

## Notes

* The `build` folder is created automatically by the build script if it does not exist.
* Empty asset folders are preserved using `.gitkeep` files.
* The `utilities` folder contains helper tools such as `projectDump` and `projectTree`.
* Build output (`build/` and `*.exe`) is ignored by Git via `.gitignore`.


## Creating a New Project

This template can be used to quickly create a new Raylib project with a clean Git history.

### 1. Create a New Repository

1. Open the **Template** repository on GitHub.
2. Click **Use this template**.
3. Select **Create a new repository**.
4. Enter a name for your new project.
5. Click **Create repository**.

GitHub will create a brand-new repository containing all of the template files without copying the commit history.

---

### 2. Clone the Repository

1. Copy the repository URL from GitHub.
2. Open **Visual Studio Code**.
3. Press **Ctrl + Shift + P** to open the Command Palette.
4. Select **Git: Clone**.
5. Paste the repository URL.
6. Choose where you would like to save the project.
7. When prompted, click **Open**.

---

### 3. Configure the Project

Before building, update the following files:

#### `include/Constants.h`

Change the window title:

```cpp
constexpr char WINDOW_TITLE[] = "Your Project Name";
```

#### `scripts/build.sh`

Change the executable name:

```bash
EXE_NAME="YourProjectName"
```

---

### 4. Build and Start Coding

Run the build script to compile the project.

Your new project is now ready for development.


## Notes

### Git

This repository is intended to be used as a reusable project template.

The default `.gitignore` has been kept intentionally minimal so that the complete project structure is included when creating a new project from this template. This allows all source files, build scripts, utility programs, assets, and Visual Studio Code configuration to be version controlled from the start.

As your project grows, you may wish to customise the `.gitignore` file to suit your own workflow.

### Example `.gitignore` Files

#### Minimal (Current Template)

```gitignore
build/
*.exe

ProjectDump.txt
FileStructure.txt
```

#### Typical Raylib / C++ Project

```gitignore
# Build output
build/

# Executables
*.exe

# Object files
*.o
*.obj

# Debug symbols
*.pdb

# Generated project files
ProjectDump.txt
FileStructure.txt

# Operating system files
Thumbs.db
.DS_Store
```

#### Visual Studio Code

```gitignore
# VS Code workspace settings
.vscode/
```

#### Ignore Utility Executables Only

This keeps the utility source code in the repository while ignoring the compiled executables.

```gitignore
utilities/*.exe
```

---

### Visual Studio Code

This template has been designed and tested for use with **Visual Studio Code**, **MSYS2 (MinGW64)**, and **Raylib**.

It includes:

* A simple and reusable project structure.
* A Bash build script (`scripts/build.sh`).
* Utility programs for generating a project tree and project dump.
* A consistent layout that can be reused for future projects.

Although the template should work with other editors and IDEs, some configuration may be required.

---

### Customising the Template

When starting a new project, remember to update the following:

* `include/Constants.h`

  * `WINDOW_TITLE`

* `scripts/build.sh`

  * `EXE_NAME`

You are then ready to start developing your new project.
