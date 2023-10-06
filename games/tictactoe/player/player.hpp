/**
 * This file contains the Player class.
 * 
 * @file player.hpp
 * 
 * @see player.cpp
 * 
 * created by Zarox28
*/

#include <string>

class Player {
  public:
    // --------------- GETTER ---------------

    /**
     * Returns the name of the player
     * 
     * @return name of the player
     *
    */
    std::string GetName();

    /**
     * Returns the symbol of the player
     * 
     * @return symbol of the player
     *
    */
    unsigned char GetSymbol();

    /**
     * Returns the score of the player
     * 
     * @return score of the player
     *
    */
    unsigned int GetScore();

    // --------------- SETTER ---------------

    /**
     * Sets the name of the player
     * 
     * @param name name of the player
     *
     * @return void
    */
    void SetName(std::string name);

    /**
     * Sets the symbol of the player
     * 
     * @param symbol symbol of the player
     *
     * @return void
    */
    void SetSymbol(unsigned char symbol);

    /**
     * Sets the score of the player
     * 
     * @param score score of the player
     *
     * @return void
    */
    void SetScore(unsigned int score);

    /**
     * Adds 1 to the score of the player
     * 
     * @return void
    */
    void AddScore();

    /**
     * Resets the score of the player
     * 
     * @return void
    */
    void ResetScore();

  private:
    // ----- ATTRIBUTES -----
    std::string name;
    unsigned char symbol;
    unsigned int score;
};