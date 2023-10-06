/**
 * @brief This file contains the Game class.
 *
 * @file game.cpp
 *
 * @see game.hpp
 *
 * created by Zarox28
 */

#include <iostream>
#include "../../../libs/termkit.cpp"

#include "../player/player.cpp"
#include "../board/board.cpp"

#include "game.hpp"

// ----- ADDPLAYER -----
void Game::AddPlayer()
{
  Player player;
  std::string name;
  unsigned char symbol;

  std::cout << "Name: ";
  std::cin >> name;
  player.SetName(name);

  std::cout << "Symbol: ";
  std::cin >> symbol;

  if (symbol == 'X' || symbol == 'x')
  {
    player.SetSymbol('x');
    players.push_back(player);
  }

  else if (symbol == 'O' || symbol == 'o')
  {
    player.SetSymbol('o');
    players.push_back(player);
  }

  else
  {
    std::cout << "Invalid symbol" << std::endl;
    AddPlayer();
  }
}

// ----- START -----
void Game::Start()
{
  AddPlayer();
  AddPlayer();
}

// ----- PLAY -----
void Game::Play()
{
}