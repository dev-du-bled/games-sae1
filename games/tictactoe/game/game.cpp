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
#include "../../../libs/utils.cpp"

#include "../player/player.cpp"
#include "../board/board.cpp"

#include "game.hpp"

void Game::DisplayLogo()
{
  std::cout << termkit::rgb_fg("████████╗██╗░█████╗░████████╗░█████╗░░█████╗░████████╗░█████╗░███████╗", 252, 127, 3) << std::endl;
  std::cout << termkit::rgb_fg("╚══██╔══╝██║██╔══██╗╚══██╔══╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗██╔════╝", 252, 127, 3) << std::endl;
  std::cout << termkit::rgb_fg("░░░██║░░░██║██║░░╚═╝░░░██║░░░███████║██║░░╚═╝░░░██║░░░██║░░██║█████╗░░", 252, 127, 3) << std::endl;
  std::cout << termkit::rgb_fg("░░░██║░░░██║██║░░██╗░░░██║░░░██╔══██║██║░░██╗░░░██║░░░██║░░██║██╔══╝░░", 252, 127, 3) << std::endl;
  std::cout << termkit::rgb_fg("░░░██║░░░██║╚█████╔╝░░░██║░░░██║░░██║╚█████╔╝░░░██║░░░╚█████╔╝███████╗", 252, 127, 3) << std::endl;
  std::cout << termkit::rgb_fg("░░░╚═╝░░░╚═╝░╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░░╚════╝░╚══════╝", 252, 127, 3) << std::endl;

  std::cout << std::endl;
}

void Game::AddPlayer(unsigned short int playerNumber)
{
  Player player;
  std::string name;
  unsigned char symbol;

  termkit::move_cursor_right(31);
  std::cout << termkit::bold_text("Player ") << termkit::rgb_fg(std::to_string(playerNumber), 255, 0, 0) << std::endl;

  std::cout << std::endl;

  std::cout << termkit::bold_text("Name: ");
  std::cin >> name;

  for (int i = 0; i < players.size(); i++)
  {
    if (players[i].GetName() == name)
    {
      std::cout << std::endl;
      std::cout << termkit::bold_text("This name is already taken!") << std::endl;
      std::cout << std::endl;

      Utils::Wait(2);
      termkit::clear();
      DisplayLogo();
      AddPlayer(playerNumber);

      return;
    }
  }

  player.SetName(name);

  std::cout << std::endl;

  std::cout << termkit::bold_text("Symbol (X/O): ");
  std::cin >> symbol;

  player.ResetScore();

  for (int i = 0; i < players.size(); i++)
  {
    if (players[i].GetSymbol() == symbol)
    {
      std::cout << std::endl;
      std::cout << termkit::bold_text("This symbol is already taken!") << std::endl;
      std::cout << std::endl;

      Utils::Wait(2);
      termkit::clear();
      DisplayLogo();
      AddPlayer(playerNumber);

      return;
    }
  }

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

    Utils::Wait(2);
    termkit::clear();
    DisplayLogo();
    AddPlayer(playerNumber);
  }

  std::cout << std::endl;
  termkit::clear();
  DisplayLogo();
}

void Game::SetBoardSize()
{
  unsigned int size;

  termkit::clear();

  std::cout << termkit::bold_text("Board size: ");
  std::cin >> size;

  board.SetSize(size);
}

void Game::Start()
{
  termkit::clear();
  termkit::set_term_title("TicTacToe");

  DisplayLogo();

  AddPlayer(1);
  AddPlayer(2);

  SetBoardSize();

  turn = 0;

  termkit::clear();
}

void Game::Play()
{
  Start();
}