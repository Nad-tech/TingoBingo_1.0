#!/bin/bash

#====================================================
# build.sh
#
# Builds the TingoBingo project using g++ and Raylib,
# then launches the executable.
#====================================================

# Exit immediately if any command fails.
set -e

EXE_NAME="TingoBingo"

# Move to the project root regardless of where the
# script was launched from.
cd "$(dirname "$0")/.."

echo "Building $EXE_NAME..."

# Create the build folder if it doesn't already exist.
mkdir -p build

# Remove any previous executable to ensure a clean build.
rm -f build/TingoBingo.exe

echo src/*.cpp

# Compile all project source files and link the
# required Raylib and Windows libraries.
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

# Launch the application in the background.
./build/$EXE_NAME.exe &