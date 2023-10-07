/**
 * @brief This file contains the Board class.
 *
 * @file board.hpp
 *
 * @see board.cpp
 *
 * created by Zarox28
 */

#include "board.hpp"

void Board::SetSize(unsigned int size)
{
  this->size = size;
}

unsigned int Board::GetSize()
{
  return size;
}