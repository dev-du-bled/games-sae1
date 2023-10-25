#!/bin/sh

build_only=false

# Check command line arguments
while [ "$1" != "" ]; do
    case $1 in
        -build-only )   build_only=true
                        ;;
        * )             ;;
    esac
    shift
done

# Check the operating system
if [ "$(uname)" = "Darwin" ]; then
    # If the operating system is macOS
    g++ -std=c++20 main.cpp -o a.out
else
    # For all other operating systems
    g++ main.cpp -o a.out
fi

# If -build-only is present, do not run the executable
if [ "$build_only" = false ]; then
    ./a.out
fi
