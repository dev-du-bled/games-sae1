/**
 * @brief This file contains the dictionary for the Hangman game
 * @file dictionary.cpp
 * @author Firmin_
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

/**
 * @brief Get a random word from the dictionary
 *
 * @return string
 */
extern string RandomWord()
{
    vector<string> mots = {"pomme", "abricot", "fenetre", "chaise", "bureau", "table", "ordinateur",
                           "clavier", "souris", "ecran", "horloge", "lampe", "porte", "poteau",
                           "voiture", "camion", "velo", "moto", "avion", "bateau", "train", "bus",
                           "pied", "onglet", "prise", "feuille", "cahier", "brosse", "moteur", "roue"};

    srand(time(0));

    int randomIndex = rand() % mots.size();

    string randomWord = mots[randomIndex];

    return randomWord;
}
