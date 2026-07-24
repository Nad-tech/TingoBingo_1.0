#!/bin/bash

set -e

# ------------------------------------------------------------
# Change the current working directory to the project root.
#
# Why?
#
# If this script lives in:
#
# Project/
# ├── scripts/
# │   └── build.sh
# ├── src/
# ├── include/
# └── tools/
#
# and you double-click it or run it from somewhere else,
# the "current directory" might not be the project folder.
#
# This line guarantees that we always start from
# the project's root directory.
# ------------------------------------------------------------

cd "$(dirname "$0")/.."

# Breakdown:
#
# $0
# ----
# The name (or path) of the script that is currently running.
#
# Example:
#
# scripts/build.sh
#
# or perhaps
#
# /home/dan/Boids/scripts/build.sh
#
# depending on how it was started.
#
#
# dirname
# -------
# Extracts only the directory portion.
#
# Example:
#
# Input:
#
# scripts/build.sh
#
# Output:
#
# scripts
#
#
# "$( ... )"
# ----------
# Command substitution.
#
# Run the command inside the brackets first,
# then use its result.
#
# Example:
#
# $(date)
#
# becomes
#
# Thu Jul 9 ...
#
#
# /..
# ----
# Means "go up one folder."
#
# If dirname returned:
#
# scripts
#
# then:
#
# scripts/..
#
# means:
#
# the parent directory
#
# which is your project folder.
#
#
# cd
# --
# Change Directory.
#
# After this command executes,
# the current directory becomes:
#
# Project/
#
# instead of
#
# Project/scripts/

# ------------------------------------------------------------
# Print the current directory.
#
# This is just for debugging.
# It's useful while learning to make sure
# you're actually in the folder you expect.
# ------------------------------------------------------------

echo "Now in:"

# pwd = Print Working Directory.
#
# It prints the folder you're currently "standing in".
#
# Example:
#
# C:/Users/Dan/Documents/Boids
#
pwd

echo "Building ProjectTree..."

g++ -std=c++23 utilities/projectTree.cpp -o utilities/projectTree.exe

echo "Executing ProjectTree..."
./utilities/projectTree.exe