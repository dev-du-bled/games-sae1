/**
 * @brief This file contains the Game class.
 *
 * @file game.hpp
 *
 * @see game.cpp
 *
 * created by Zarox28
 */

class Game
{
public:
  /**
   * @brief Displays the logo of the game
   *
   * @return void
   */
  void DisplayLogo();

  /**
   * @brief Adds a player to the game
   *
   * @param playerNumber number of the player
   *
   * @return void
   */
  void AddPlayer(unsigned short int playerNumber);

  /**
   * @brief Starts the game
   *
   * @return void
   */
  void Start();

  /**
   * @brief Sets the size of the board
   *
   * @return void
   *
   */
  void SetBoardSize();

  /**
   * @brief Plays the game
   *
   * @return void
   */
  void Play();

private:
  // ----- ATTRIBUTES -----
  std::vector<Player> players;
  unsigned int turn;
  Board board;
};