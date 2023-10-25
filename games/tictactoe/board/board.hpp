/**
 * @file  board.hpp
 * @brief This file contains the TicTacToe board class
 * @see board.cpp
 * @author Zarox28
 */

#include <vector>

class Board
{
public:
  /**
   * @brief Sets the size of the board
   *
   * @param [in] size size of the board
   *
   * @return void
   */
  void setSize(unsigned short size);

  /**
   * @brief Sets the position of the player
   *
   * @param [in] postion position of the player
   * @param [in] symbol symbol of the player
   *
   * @return bool
   */
  bool setPosition(std::vector<int> postion, char symbol);

  /**
   * @brief Draw the board
   *
   * @return void
   */
  void draw();

  /**
   * @brief Returns the size of the board
   *
   * @return size of the board
   */
  unsigned short getSize();

  /**
   * @brief Returns the grid
   *
   * @return grid
   */
  std::vector<std::vector<char>> getGrid();

private:
  // ----- ATTRIBUTES -----
  unsigned short size;
  std::vector<std::vector<char>> grid;
};