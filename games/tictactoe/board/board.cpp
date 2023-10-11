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
#include <iostream>
#include <regex>
#include <vector>

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
    if (std::regex_match(std::to_string(postion[0]), std::regex("[0-9]+")) == false || std::regex_match(std::to_string(postion[1]), std::regex("[0-9]+")) == false)
    {
      return false;
    }

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

      if (k % 2 == 0)
      {
        std::cout << termkit::rgb_fg(termkit::bold_text(std::string(1, grid[k][j])), 255, 0, 0);
      }
      else
      {
        std::cout << termkit::rgb_fg(termkit::bold_text(std::string(1, grid[k][j])), 0, 0, 255);
      }

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

std::vector<std::vector<char>> Board::GetGrid()
{
  return grid;
}