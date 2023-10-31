#include "libs/termkit.hpp"
#include <iostream>
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

extern void showMenu(std::vector<MenuEntry> games) {
  
  unsigned short selected_option = 0;
  bool is_selecting = true;
  std::string selected_game_display_name = games[0].displayName;
  unsigned short ui_vcenter_point = (10 + games.size()) / 2;
  //                                 ^^
  // Height of the logo + it's padding and version number

  termkit::clear();
  termkit::hide_cursor();

  termkit::move_cursor_down(ui_vcenter_point);
  // in case some OS doesn't support the moving the cursor using a CSI here is a legacy way of moving it
  // for (unsigned short k = 0; k < ui_vcenter_point + 1; k++) std::cout << std::endl;

  std::cout << termkit::center_text_block(termkit::rgb_fg(title, 255, 0, 0, true), 98)
            << termkit::DEFAULT_TERM_STYLE << std::endl;

  std::cout << termkit::center_line(std::string(58, ' ') + termkit::bold_text("v0.0.1"))
            << std::endl;

  std::cout << std::endl;

  while (is_selecting) {
    // render
    for (unsigned long i = 0; i < games.size(); i++) {
      selected_game_display_name = games[i].displayName;
      if (i == selected_option) {
        std::cout << termkit::center_line(termkit::bold_text(termkit::rgb_fg(selected_game_display_name, 255, 0, 0)), selected_game_display_name.length())
                  << std::endl;
      } else
        std::cout << termkit::center_line(selected_game_display_name, selected_game_display_name.length())
                  << std::endl;
    }
    termkit::move_cursor_up(games.size());

    // keyboard input
    switch (termkit::getch()) {
    case CTRLC:
      return;

    case TAB:
      selected_option = (selected_option + 1) % games.size();
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
      char g = termkit::getch();
      switch (g) {
      case UP:
        selected_option = (selected_option - 1) % games.size();
        continue;

      case DOWN:
        selected_option = (selected_option + 1) % games.size();
        continue;

      case BAKTAB:
        selected_option = (selected_option - 1) % games.size();
        continue;
        // debugging
        // default:
        //   printf("%i", g);
      }
#else // windows support
    case WINUP:
      selected_option = (selected_option - 1) % games.size();
      continue;
    case WINDOWN:
      selected_option = (selected_option + 1) % games.size();
      continue;
#endif
    }
  }

  termkit::clear();
  termkit::show_cursor();

  games[selected_option].exec();
  
}
