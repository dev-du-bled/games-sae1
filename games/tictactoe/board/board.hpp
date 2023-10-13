/**
 * This file contains the Board class.
 *
 * @file board.hpp
 *
 * @see board.cpp
 *
 * created by Zarox28
 */

#include <vector>

class Board
{
public:
  /**
   * @brief Sets the size of the board
   *
   * @param size size of the board
   *
   * @return void
   *
   */
  void SetSize(unsigned short size);

  /**
   * @brief Sets the position of the player
   *
   * @param postion position of the player
   *
   * @param symbol symbol of the player
   *
   * @return bool
   *
   */
  bool SetPosition(std::vector<int> postion, char symbol);

  /**
   * @brief Draw the board
   *
   * @return void
   *
   */
  void Draw();

  /**
   * @brief Returns the size of the board
   *
   * @return size of the board
   *
   */
  unsigned short GetSize();

  /**
   * @brief Returns the grid
   *
   * @return grid
   *
   */
  std::vector<std::vector<char>> GetGrid();

private:
  // ----- ATTRIBUTES -----
  unsigned short size;
  std::vector<std::vector<char>> grid;
};