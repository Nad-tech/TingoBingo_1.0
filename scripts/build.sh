#!/bin/bash

set -e

EXE_NAME="TingoBingo"

cd "$(dirname "$0")/.."

echo "Building $EXE_NAME..."

mkdir -p build

rm -f build/TingoBingo.exe

echo src/*.cpp

g++ \
    -g \
    -Wall \
    -Wextra \
    -std=c++23 \
    -Iinclude \
    src/*.cpp \
    src/head/*.cpp \
    -o build/$EXE_NAME.exe \
    -lraylib \
    -lopengl32 \
    -lgdi32 \
    -lwinmm

echo "Build successful"
echo "Running $EXE_NAME..."

./build/$EXE_NAME.exe &


# ============================================================
# COMMENTED REFERENCE
# ============================================================

# #!/bin/bash
# Run this script using Bash.
#
# set -e
# Stop the script immediately if a command fails.
#
# EXE_NAME="TingoBingo"
# Set the name of the executable.
#
# cd "$(dirname "$0")/.."
# Move from the scripts directory to the project root.
#
# echo "Building $EXE_NAME..."
# Display a message showing that compilation is starting.
#
# mkdir -p build
# Create the build directory if it does not already exist.
#
# g++ \
# Start the C++ compiler.
#
#     -g \
# Include debugging information for GDB.
#
#     -Wall \
# Enable common compiler warnings.
#
#     -Wextra \
# Enable additional compiler warnings.
#
#     -std=c++23 \
# Compile using the C++23 standard.
#
#     -Iinclude \
# Tell the compiler to search the include directory for headers.
#
#     src/*.cpp \
# Compile all .cpp files directly inside src.
#
#     src/head/*.cpp \
# Compile all .cpp files inside src/head.
#
#     -o build/$EXE_NAME.exe \
# Create the executable inside the build directory.
#
#     -lraylib \
# Link the Raylib library.
#
#     -lopengl32 \
# Link the Windows OpenGL library.
#
#     -lgdi32 \
# Link the Windows Graphics Device Interface library.
#
#     -lwinmm
# Link the Windows multimedia library.
#
# echo "Build successful"
# Display a message when compilation succeeds.
#
# echo "Running $EXE_NAME..."
# Display a message before running the program.
#
# ./build/$EXE_NAME.exe &
# Run the executable in the background.