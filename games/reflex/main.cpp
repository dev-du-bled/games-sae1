/**
 * @brief This file contains the Reflex game.
 *
 * @file main.cpp
 *
 * created by Zarox28
 */

#include <iostream>
#include <chrono>
#include <string>

#include "../../libs/termkit.cpp"
#include "../../libs/utils.cpp"

std::string previousTime[2] = {"0", "0"};
unsigned short color[3] = {255, 255, 255};

enum SPACE_KEY
{
  SPACE = 32
};

// ----- DISPLAY LOGO -----
void DisplayLogo()
{
  const char *logo = R"( ____       __ _           
|  _ \ ___ / _| | _____  __
| |_) / _ \ |_| |/ _ \ \/ /
|  _ <  __/  _| |  __/>  < 
|_| \_\___|_| |_|\___/_/\_\
)";

  std::cout << termkit::rgb_fg(termkit::center_text_block(logo), 52, 131, 235) << std::endl;
  std::cout << termkit::bold_text(termkit::center_line("By Zarox28")) << std::endl;
}

// ----- DISPLAY SQUARE -----
void DisplaySquare(bool color)
{
  if (color)
  {
    std::cout << termkit::rgb_fg(termkit::center_line("Click!"), 255, 255, 255) << std::endl;
    std::cout << std::endl;
  }
  else
  {
    std::cout << std::endl;
    std::cout << std::endl;
  }

  for (unsigned short j = 0; j < 20; j++)
  {
    for (unsigned short i = 0; i < 60; i++)
    {
      if (color)
      {
        std::cout << termkit::rgb_fg("■", 0, 255, 0);
      }
      else
      {
        std::cout << termkit::rgb_fg("■", 255, 0, 0);
      }
    }

    std::cout << std::endl;
  }
}

// ----- START -----
void Start()
{
  termkit::clear();

  DisplayLogo();

  std::cout << std::endl;
  std::cout << termkit::bold_text(termkit::center_line("   Press any key to start the game...")) << std::endl;
  std::cout << std::endl;
  std::cout << termkit::bold_text(termkit::center_line("   Press Ctrl+C to exit the game")) << std::endl;
  std::cout << std::endl;

  switch (termkit::getch())
  {
  case 3:
    termkit::clear();
    termkit::show_cursor();
    exit(0);

  default:
    break;
  }

  termkit::clear();
}

// ----- PLAY -----
void Play()
{
  while (true)
  {
    DisplaySquare(0);

    Utils::Wait(rand() % 5 + 1);

    termkit::clear();

    DisplaySquare(1);

    auto startTime = std::chrono::high_resolution_clock::now();

    while (!termkit::getch())
    {
      continue;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto durationSeconds = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    termkit::clear();

    previousTime[1] = std::to_string(durationSeconds.count()) + "." + std::to_string(durationMs.count() % 1000);
    std::cout << "Previous time: " << termkit::bold_text(previousTime[0] + "s") << std::endl;

    if (previousTime[1] == previousTime[0])
    {
      std::cout << termkit::bold_text(termkit::center_line("   You have the same time as before!")) << std::endl;
      color[0] = 66;
      color[1] = 158;
      color[2] = 245;
    }
    else if (previousTime[0] == "0")
    {
      std::cout << termkit::bold_text(termkit::center_line("   This is your first time!")) << std::endl;
      for (unsigned short i = 0; i < 3; i++)
      {
        color[i] = 255;
      }
    }
    else if (previousTime[1] < previousTime[0])
    {
      std::cout << termkit::bold_text(termkit::center_line("   You beat the previous time!")) << std::endl;
      color[0] = 28;
      color[1] = 189;
      color[2] = 52;
    }
    else
    {
      std::cout << termkit::bold_text(termkit::center_line("   You didn't beat the previous time!")) << std::endl;
      color[0] = 245;
      color[1] = 168;
      color[2] = 34;
    }

    std::cout << "Reaction time: " << termkit::rgb_fg(termkit::bold_text(std::to_string(durationSeconds.count()) + "." + std::to_string(durationMs.count() % 1000) + "s"), color[0], color[1], color[2]) << std::endl;
    std::cout << std::endl;

    previousTime[0] = previousTime[1];

    Utils::Wait(2);

    termkit::clear();

    std::cout << termkit::bold_text(termkit::center_line("   Press any key to continue...")) << std::endl;
    std::cout << std::endl;
    std::cout << termkit::bold_text(termkit::center_line("   Press Ctrl+C to exit the game")) << std::endl;

    switch (termkit::getch())
    {
    case 3:
      termkit::clear();
      termkit::show_cursor();
      exit(0);

    default:
      termkit::clear();
      Play();
    }
  }
}

// ----- MAIN -----
void reflex()
{
  termkit::hide_cursor();

  Start();
  Play();
}