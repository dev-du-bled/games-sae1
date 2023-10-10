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
   * @brief Checks if the game is over
   *
   * @return bool
   *
   */
  bool IsOver();

  /**
   * @brief Checks if the game is a draw
   *
   * @param grid grid of the game
   * @param symbol symbol of the player
   *
   * @return bool
   *
   */
  bool IsWin(std::vector<std::vector<char>> grid, char symbol);

  /**
   * @brief Plays the game
   *
   * @return void
   */
  void Play();

private:
  // ----- ATTRIBUTES -----
  std::vector<Player> players;
  unsigned short int turn;
  unsigned short int moves;
  unsigned short int actualMove;
  unsigned short int position;
  Board board;
};