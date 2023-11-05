/**
 * @file game.cpp
 * @brief This file contains the TicTacToe game class
 * @see game.hpp
 * @author Zarox28
 */

#include <iostream>
#include <vector>

#include "../../../libs/termkit/termkit.cpp"
#include "../../../libs/utils.cpp"

#include "../player/player.cpp"
#include "../board/board.cpp"

#include "game.hpp"

void Game::displayLogo()
{
  const char *logo =
      R"( _____ _     _____         _____
|_   _(_) __|_   _|_ _  __|_   _|__   ___
  | | | |/ __|| |/ _` |/ __|| |/ _ \ / _ \
  | | | | (__ | | (_| | (__ | | (_) |  __/
  |_| |_|\___||_|\__,_|\___||_|\___/ \___|
)";

  std::cout << termkit::rgb_fg(termkit::center_text_block(logo, 43), 252, 157, 3) << std::endl;
  std::cout << termkit::bold_text(termkit::center_line("By Zarox28")) << std::endl;
  std::cout << std::endl;
}

void Game::addPlayer(unsigned short playerNumber)
{
  Player player;
  std::string name;
  std::string symbolInput;
  unsigned char symbol;

  displayLogo();

  std::cout << termkit::bold_text(termkit::center_line("player ")) << termkit::rgb_fg(std::to_string(playerNumber), 255, 0, 0) << std::endl;

  std::cout << std::endl;

  std::cout << termkit::bold_text("Name: ");
  std::cin >> name;

  if (name.length() > 10 || name.length() < 1)
  {
    std::cout << std::endl;
    std::cout << termkit::bold_text("Name must be between 1 and 10 characters!") << std::endl;
    std::cout << std::endl;

    Utils::wait(2);
    termkit::clear();

    addPlayer(playerNumber);
  }

  if (!std::regex_match(name, std::regex("[a-zA-Z]+")))
  {
    std::cout << std::endl;
    std::cout << termkit::bold_text("Name must only contain letters!") << std::endl;
    std::cout << std::endl;

    Utils::wait(2);
    termkit::clear();

    addPlayer(playerNumber);
  }

  if (players.size() == 1)
  {
    if (players[0].getName() == name)
    {
      std::cout << std::endl;
      std::cout << termkit::bold_text("This name is already taken!") << std::endl;
      std::cout << std::endl;

      Utils::wait(2);
      termkit::clear();

      addPlayer(playerNumber);
    }
  }

  player.setName(name);

  std::cout << std::endl;

  player.resetScore();

  std::cout << termkit::bold_text("Symbol: ");
  std::cin >> symbolInput;
  symbol = symbolInput[0];

  if (players.size() == 1)
  {
    if (symbol == players[0].getSymbol())
    {
      std::cout << std::endl;
      std::cout << termkit::bold_text("This symbol is already taken!") << std::endl;
      std::cout << std::endl;

      Utils::wait(2);
      termkit::clear();

      addPlayer(playerNumber);
    }
  }

  player.setSymbol(tolower(symbol));

  players.push_back(player);

  std::cout << std::endl;
  termkit::clear();
}

void Game::setBoardSize()
{
  unsigned int size;

  termkit::clear();

  displayLogo();

  std::cout << termkit::bold_text("Board size: ");
  std::cin >> size;

  if (size >= 3 && size <= 100)
  {
    board.setSize(size);
  }
  else
  {
    std::cout << std::endl;
    std::cout << termkit::bold_text("Board size must be between 3 and 100!") << std::endl;
    std::cout << std::endl;

    Utils::wait(2);
    termkit::clear();

    setBoardSize();
  }
}

void Game::start()
{
  termkit::clear();
  termkit::set_term_title("TicTacToe");

  addPlayer(1);
  addPlayer(2);

  setBoardSize();

  turn = 0;
  actualMove = 0;
  moves = board.getSize() * board.getSize();

  termkit::clear();
}

bool Game::isWin(std::vector<std::vector<char>> grid, char symbol)
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

bool Game::isOver()
{
  if (isWin(board.getGrid(), players[turn].getSymbol()))
  {
    std::cout << std::endl;
    std::cout << termkit::bold_text(players[turn].getName()) << " (" << players[turn].getSymbol() << ") " << termkit::bold_text("won!") << std::endl;
    std::cout << std::endl;

    players[turn].addScore();

    std::cout << players[0].getName() << ": " << players[0].getScore() << std::endl;
    std::cout << players[1].getName() << ": " << players[1].getScore() << std::endl;
    std::cout << std::endl;

    actualMove = 0;
    turn = 0;

    Utils::wait(3);
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

    Utils::wait(2);
    termkit::clear();

    return true;
  }

  return false;
}

void Game::play()
{
  unsigned short x;
  unsigned short y;

  while (true)
  {
    termkit::clear();

    displayLogo();

    std::cout << players[turn].getName() << "'s turn (" << termkit::bold_text(std::string(1, players[turn].getSymbol())) << ")" << std::endl;
    std::cout << std::endl;

    board.draw();

    std::cout << std::endl;

    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;

    if (board.setPosition({x - 1, y - 1}, players[turn].getSymbol()))
    {
      actualMove++;

      if (isOver())
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

      Utils::wait(2);
      termkit::clear();
    }
  }

  board.setSize(board.getSize());
  play();
}
