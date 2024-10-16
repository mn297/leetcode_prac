#!/bin/bash

# Check if the source file is passed as an argument
if [ $# -lt 1 ]; then
    echo "Usage: $0 source_file.cpp"
    exit 1
fi

# Set the source file as the argument
SRC="$1"

# Run make with the provided source file and then execute the output
make SRC="$SRC" && ./leetcode.out
