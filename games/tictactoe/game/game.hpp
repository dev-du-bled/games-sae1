/**
 * @brief This file contains the Game class.
 * 
 * @file game.hpp
 *
 * @see game.cpp
 * 
 * created by Zarox28
*/

class Game {
  public:
    /**
     * Adds a player to the game
     * 
     * @return void
    */
    void AddPlayer();

    /**
     * Starts the game
     * 
     * @return void
    */
    void Start();

  private:
    std::vector<Player> players;
};