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
#include <vector>

#include "../../../libs/termkit.cpp"
#include "../../../libs/utils.cpp"

#include "../player/player.cpp"
#include "../board/board.cpp"

#include "game.hpp"

void Game::DisplayLogo()
{
  const char *logo =
      R"( _____ _     _____         _____
|_   _(_) __|_   _|_ _  __|_   _|__   ___
  | | | |/ __|| |/ _` |/ __|| |/ _ \ / _ \
  | | | | (__ | | (_| | (__ | | (_) |  __/
  |_| |_|\___||_|\__,_|\___||_|\___/ \___|
)";

  std::cout << termkit::rgb_fg(logo, 252, 157, 3) << std::endl;
}

void Game::AddPlayer(unsigned short playerNumber)
{
  Player player;
  std::string name;
  unsigned char symbol;

  std::cout << termkit::bold_text(termkit::center_line("Player ")) << termkit::rgb_fg(std::to_string(playerNumber), 255, 0, 0) << std::endl;

  std::cout << std::endl;

  std::cout << termkit::bold_text("Name: ");
  std::cin >> name;

  for (unsigned short i = 0; i < players.size(); i++)
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

  std::cout << termkit::bold_text("Symbol: ");
  std::cin >> symbol;

  if (symbol == ' ' || std::string(1, symbol).length() > 1)
  {
    std::cout << std::endl;
    std::cout << termkit::bold_text("Symbol not allowed!") << std::endl;
    std::cout << std::endl;

    Utils::Wait(2);
    termkit::clear();
    DisplayLogo();
    AddPlayer(playerNumber);

    return;
  }

  if (players.size() == 1)
  {
    if (symbol == players[0].GetSymbol())
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

  player.SetSymbol(tolower(symbol));

  players.push_back(player);

  std::cout << std::endl;
  termkit::clear();
  DisplayLogo();
}

void Game::SetBoardSize()
{
  unsigned int size;

  termkit::clear();

  DisplayLogo();

  std::cout << termkit::bold_text("Board size: ");
  std::cin >> size;

  if (size < 3 || size > 100)
  {
    std::cout << std::endl;
    std::cout << termkit::bold_text("Board size must be between 3 and 100!") << std::endl;
    std::cout << std::endl;

    Utils::Wait(2);
    termkit::clear();
    DisplayLogo();
    SetBoardSize();
  }

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
  for (unsigned short i = 0; i < grid.size(); i++)
  {
    bool rowWin = true;
    bool colWin = true;

    for (unsigned short j = 0; j < grid.size(); j++)
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

  for (unsigned short i = 0; i < grid.size(); i++)
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
  if (IsWin(board.GetGrid(), players[turn].GetSymbol()))
  {
    std::cout << std::endl;
    std::cout << termkit::bold_text(players[turn].GetName()) << " (" << players[turn].GetSymbol() << ") " << termkit::bold_text("won!") << std::endl;
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

  if (actualMove == moves)
  {
    std::cout << std::endl;
    std::cout << "It's a draw!" << std::endl;
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
  unsigned short x;
  unsigned short y;

  while (true)
  {
    termkit::clear();

    DisplayLogo();

    std::cout << players[turn].GetName() << "'s turn (" << termkit::bold_text(std::string(1, players[turn].GetSymbol())) << ")" << std::endl;
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

      if (IsOver())
      {
        break;
      }

      turn = 1 - turn;
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