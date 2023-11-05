#include "libs/termkit/termkit.cpp"
#include <iostream>
#include <sys/types.h>
#include <vector>

const char *title =
    R"(
 ██████╗███████╗██╗     ███████╗ █████╗ ████████╗   █████╗    ██████╗  █████╗ ███╗   ███╗███████╗
██╔════╝██╔════╝██║     ██╔════╝██╔══██╗╚══██╔══╝  ██╔══██╗  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝
╚█████╗ █████╗  ██║     █████╗  ██║  ╚═╝   ██║     ███████║  ██║  ██╗ ███████║██╔████╔██║█████╗  
 ╚═══██╗██╔══╝  ██║     ██╔══╝  ██║  ██╗   ██║     ██╔══██║  ██║  ╚██╗██╔══██║██║╚██╔╝██║██╔══╝  
██████╔╝███████╗███████╗███████╗╚█████╔╝   ██║     ██║  ██║  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗
╚═════╝ ╚══════╝╚══════╝╚══════╝ ╚════╝    ╚═╝     ╚═╝  ╚═╝   ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝
  )";

enum Keys {
  CTRLC = 3,
  TAB = 9,
  ENTER = 13,
  ESC = 27,
  UP = 65,
  DOWN = 66,
  // Windows has different keycodes for up and down arrows
  WINUP = 72,
  WINDOWN = 80,
  BAKTAB = 90,
  BRACKET = 91
};

class MenuEntry {
public:
  void (*exec)();
  std::string displayName;

  MenuEntry(void (*callee)(), std::string name) {
    this->exec = callee;
    this->displayName = name;
  }
};

void displayTitle() {
  std::cout << termkit::center_text_block(termkit::rgb_fg(title, 255, 0, 0, true), 98)
            << termkit::DEFAULT_TERM_STYLE << std::endl;
  std::cout << termkit::center_line(std::string(58, ' ') + termkit::bold_text("v0.0.1"))
            << std::endl;
  std::cout << std::endl;
  
}

void renderSelectable(std::vector<MenuEntry> &games, unsigned short selected_option) {
  std::string selected_game_display_name = games[0].displayName;     
  for (unsigned long i = 0; i < games.size() ; i++) {
      selected_game_display_name = games[i].displayName;
      if (i == selected_option) {
        std::cout << termkit::center_line(termkit::bold_text(termkit::rgb_fg(selected_game_display_name, 255, 0, 0)), selected_game_display_name.length())
                  << std::endl;
      } else
        std::cout << termkit::center_line(selected_game_display_name, selected_game_display_name.length())
                  << std::endl;
    }
  
}

void incrementSelectedOption(ushort &selected_option, ulong number_of_games) {
  selected_option += 1;
  selected_option %= number_of_games;
}

void decrementSelectedOption(ushort &selected_option, ulong number_of_games) {
  selected_option -= 1;
  selected_option %= number_of_games;
}


extern void showMenu(std::vector<MenuEntry> games) {
  const ulong number_of_games = games.size();
  const ushort terminal_height = termkit::get_term_size().height;
  const ushort ui_vcenter_point = (12 + number_of_games) / 2;
  //                               ^^
  // Height of the logo + it's padding and version number
  
  menuStart : {
  ushort selected_option = 0;
  bool is_selecting = true;

  termkit::clear();
  termkit::hide_cursor();

  termkit::move_cursor_down(terminal_height/2 - ui_vcenter_point);

  displayTitle();

  while (is_selecting) {
    // render
    renderSelectable(games, selected_option);
    termkit::move_cursor_up(games.size());

    // keyboard input
    switch (termkit::getch()) {
    case CTRLC: return;

    case TAB:
      incrementSelectedOption(selected_option, number_of_games);
      continue;

    case ENTER:
      is_selecting = false;
      break;
// handle multi-character keys '^[' e.i UP arrow is ^[A
//                                                  27 91 A
#if defined(unix) || defined(__APPLE__) // linux and mac support
    case ESC:
      if (termkit::getch() != BRACKET)
        continue;

      /* 
        As said a couple of lines before, on UNIX-like systems arrow keys are composed of 3 characters, the first being the escape one (code 27 '^')
        the second being an openning bracket (code 91 '[')
        the last one being the character identifying the key
      */
      char g = termkit::getch();

      switch (g) {
      case UP:
        decrementSelectedOption(selected_option, number_of_games);
        continue;

      case DOWN:
        incrementSelectedOption(selected_option, number_of_games);
        continue;

      case BAKTAB:
        decrementSelectedOption(selected_option, number_of_games);
        continue;
      }

// Windows support
#else
    case WINUP:
      decrementSelectedOption(selected_option, number_of_games);
      continue;
    case WINDOWN:
      incrementSelectedOption(selected_option, number_of_games);
      continue;
#endif
    }
  }

  termkit::clear();
  termkit::show_cursor();

  games[selected_option].exec();  
  }
  goto menuStart;
}
