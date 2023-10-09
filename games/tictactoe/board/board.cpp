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

void Board::SetSize(unsigned short int size)
{
  this->size = size;

  this->grid.resize(size, std::vector<char>(size));

  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      grid[i][j] = ' ';
    }
  }
}

bool Board::SetPosition(std::vector<int> postion, char symbol)
{
  if (postion[0] < size && postion[1] < size && postion[0] >= 0 && postion[1] >= 0)
  {
    if (grid[postion[0]][postion[1]] == ' ')
    {
      grid[postion[0]][postion[1]] = symbol;

      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }

  return false;
}

void Board::Draw()
{
  for (unsigned int j = 0; j < size; j++)
  {
    for (unsigned int i = 0; i < size; i++)
    {
      if (j > 0)
        std::cout << "--- ";
    }

    if (j > 0)
      std::cout << std::endl;

    for (unsigned int k = 0; k < size; k++)
    {
      std::cout << " ";
      std::cout << grid[k][j];

      if (k < size - 1)
      {
        std::cout << " ";
        std::cout << "|";
      }
    }

    std::cout << std::endl;
  }
}

unsigned short int Board::GetSize()
{
  return size;
}

unsigned short int Board::GetPosition(std::vector<int> position)
{
  return grid[position[0]][position[1]];
}

std::vector<std::vector<char>> Board::GetGrid()
{
  return grid;
}