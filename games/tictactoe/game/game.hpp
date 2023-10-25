/**
 * @brief This file contains the Game class.
 *
 * @file game.hpp
 *
 * @see game.cpp
 *
 * created by Zarox28
 */

#include <vector>

class Game
{
public:
  /**
   * @brief Displays the logo of the game
   *
   * @return void
   */
  void displayLogo();

  /**
   * @brief Adds a player to the game
   *
   * @param playerNumber number of the player
   *
   * @return void
   */
  void addPlayer(unsigned short playerNumber);

  /**
   * @brief Starts the game
   *
   * @return void
   */
  void start();

  /**
   * @brief Sets the size of the board
   *
   * @return void
   *
   */
  void setBoardSize();

  /**
   * @brief Checks if the game is over
   *
   * @return bool
   *
   */
  bool isOver();

  /**
   * @brief Checks if the game is a draw
   *
   * @param grid grid of the game
   * @param symbol symbol of the player
   *
   * @return bool
   *
   */
  bool isWin(std::vector<std::vector<char>> grid, char symbol);

  /**
   * @brief Plays the game
   *
   * @return void
   */
  void play();

private:
  // ----- ATTRIBUTES -----
  std::vector<Player> players;
  unsigned short turn;
  unsigned short moves;
  unsigned short actualMove;
  Board board;
};