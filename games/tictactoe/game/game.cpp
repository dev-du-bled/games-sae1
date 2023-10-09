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

  for (unsigned short int i = 0; i < players.size(); i++)
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

  player.ResetScore();

  if (players.size() == 1)
  {
    players[0].GetSymbol() == 'x' ? player.SetSymbol('o') : player.SetSymbol('x');
    players.push_back(player);
  }
  else
  {
    std::cout << termkit::bold_text("Symbol: ");
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

      Utils::Wait(2);
      termkit::clear();
      DisplayLogo();
      AddPlayer(playerNumber);
    }
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
  moves = board.GetSize() * board.GetSize();
  actualMove = 0;

  termkit::clear();
}

bool Game::IsWin(std::vector<std::vector<char>> grid, char symbol)
{
  for (unsigned short int i = 0; i < grid.size(); i++)
  {
    bool rowWin = true;
    bool colWin = true;

    for (unsigned short int j = 0; j < grid.size(); j++)
    {
      if (grid[i][j] != symbol)
      {
        rowWin = false;
      }
      if (grid[j][i] != symbol)
      {
        colWin = false;
      }
    }
    if (rowWin || colWin)
    {
      return true;
    }
  }

  bool diag1Win = true;
  bool diag2Win = true;

  for (unsigned short int i = 0; i < grid.size(); i++)
  {
    if (grid[i][i] != symbol)
    {
      diag1Win = false;
    }
    if (grid[i][grid.size() - 1 - i] != symbol)
    {
      diag2Win = false;
    }
  }
  if (diag1Win || diag2Win)
  {
    return true;
  }

  return false;
}

bool Game::IsOver()
{
  if (actualMove == moves)
  {
    return true;
  }

  if (IsWin(board.GetGrid(), players[turn].GetSymbol()))
  {
    std::cout << std::endl;
    std::cout << termkit::bold_text(players[turn].GetName()) << termkit::bold_text(" won!") << std::endl;
    std::cout << std::endl;

    players[turn].AddScore();

    std::cout << players[0].GetName() << ": " << players[0].GetScore() << std::endl;
    std::cout << players[1].GetName() << ": " << players[1].GetScore() << std::endl;
    std::cout << std::endl;

    actualMove = 0;
    turn = 0;

    Utils::Wait(2);
    termkit::clear();

    return true;
  }

  return false;
}

void Game::Play()
{
  while (!IsOver())
  {
    unsigned short int x;
    unsigned short int y;
    termkit::clear();

    std::cout << players[turn].GetName() << "'s turn" << std::endl;
    std::cout << std::endl;
    board.Draw();

    std::cout << std::endl;
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;

    if (board.SetPosition({x - 1, y - 1}, players[turn].GetSymbol()))
    {
      actualMove++;
      if (turn == 0)
      {
        turn = 1;
      }
      else
      {
        turn = 0;
      }
    }
    else
    {
      std::cout << std::endl;
      std::cout << termkit::bold_text("This position is already taken or value is not possible!") << std::endl;
      std::cout << std::endl;

      Utils::Wait(2);
      termkit::clear();
      continue;
    }
  }

  board.SetSize(board.GetSize());
  Play();
}