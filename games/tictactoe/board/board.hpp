/**
 * This file contains the Board class.
 *
 * @file board.hpp
 *
 * @see board.cpp
 *
 * created by Zarox28
 */

class Board
{
public:
  /**
   * @brief Returns the size of the board
   *
   * @param size size of the board
   *
   * @return size of the board
   *
   */
  void SetSize(unsigned int size);

  /**
   * @brief Returns the size of the board
   *
   * @return size of the board
   *
   */
  unsigned int GetSize();

private:
  // ----- ATTRIBUTES -----
  unsigned int size;
};