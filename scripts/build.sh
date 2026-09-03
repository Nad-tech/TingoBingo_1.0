#!/bin/bash

#====================================================
# build.sh
#
# Builds and runs TingoBingo using Make.
#====================================================

set -e

# Move to the project root regardless of where the
# script was launched from.
cd "$(dirname "$0")/.."

echo "Building TingoBingo..."

mingw32-make

echo
echo "Build successful."
echo "Running TingoBingo..."
echo

./build/TingoBingo.exe &

