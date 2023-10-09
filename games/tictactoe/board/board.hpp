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
  void SetSize(unsigned short int size);

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
  unsigned short int GetSize();

  /**
   * @brief Returns the position of the player
   *
   * @param position position of the player
   *
   * @return position of the player
   *
   */
  unsigned short int GetPosition(std::vector<int> position);

  /**
   * @brief Returns the grid
   *
   * @return grid
   *
   */
  std::vector<std::vector<char>> GetGrid();

private:
  // ----- ATTRIBUTES -----
  unsigned short int size;
  std::vector<std::vector<char>> grid;
};