/*
 * This file contains the Player class.
 * 
 * @file player.hpp
 * 
 * @see player.cpp
 * 
 * created by Zarox28
*/

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

  private:
    // ----- ATTRIBUTES -----
    std::string name;
    unsigned char symbol;
    unsigned int score;
};