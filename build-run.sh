#!/bin/sh

build_only=false

# Vérification des arguments de ligne de commande
while [ "$1" != "" ]; do
    case $1 in
        -build-only )   build_only=true
                        ;;
        * )             ;;
    esac
    shift
done

# Vérification du système d'exploitation
if [ "$(uname)" = "Darwin" ]; then
    # Si le système d'exploitation est macOS
    g++ -std=c++20 main.cpp -o a.out
else
    # Pour tous les autres systèmes d'exploitation
    g++ main.cpp -o a.out
fi

# Si -build-only est présent, n'exécutez pas l'exécutable
if [ "$build_only" = false ]; then
    ./a.out
fi
