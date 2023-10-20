#include "libs/termkit.hpp"
#include <iostream>
#include <random>
#include <vector>

const char *title =
    R"( _____ _____ _      _____ _____ _____     ___    _____   ___  ___  ___ _____ 
/  ___|  ___| |    |  ___/  __ \_   _|  / _ \   |  __ \ / _ \ |  \/  ||  ___|
\ `--.| |__ | |    | |__ | /  \/ | |   / /_\ \  | |  \// /_\ \| .  . || |__  
 `--. \  __|| |    |  __|| |     | |   |  _  |  | | __ |  _  || |\/| ||  __| 
/\__/ / |___| |____| |___| \__/\ | |   | | | |  | |_\ \| | | || |  | || |___ 
\____/\____/\_____/\____/ \____/ \_/   \_| |_/   \____/\_| |_/\_|  |_/\____/
)";

enum Keys {
  CTRLC = 3,
  TAB = 9,
  ENTER = 13,
  ESC = 27,
  UP = 65,
  DOWN = 66,
  BAKTAB = 90,
  BRACKET = 91
};

class MenuEntry {
public:
  void (*exec)();
  std::string dislayName;

  MenuEntry(void (*callee)(), std::string name) {
    this->exec = callee;
    this->dislayName = name;
  }
};

extern void showMenu(std::vector<MenuEntry> games) {
  unsigned short selected_option = 0;
  bool is_selecting = true;

  termkit::clear();
  termkit::hide_cursor();

  std::cout << termkit::rgb_fg(termkit::center_text_block(title), 255, 0, 0)
            << std::endl;

  std::cout << termkit::center_line(std::string(52, ' ') +
                                    termkit::bold_text("v0.0.1"))
            << std::endl;

  std::cout << std::endl;

  while (is_selecting) {
    // render
    for (int i = 0; i < games.size(); i++) {
      if (i == selected_option) {
        std::cout << termkit::rgb_fg(termkit::center_line(games[i].dislayName),
                                     255, 0, 0)
                  << std::endl;
      } else
        std::cout << termkit::center_line(games[i].dislayName) << std::endl;
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
        // default:
        //   printf("%i", g);
      }
#else // windows support
    case 72:
      selected_option = (selected_option - 1) % games.size();
      continue;
    case 80:
      selected_option = (selected_option + 1) % games.size();
      continue;
#endif
    }
  }

  termkit::clear();
  termkit::show_cursor();

  games[selected_option].exec();
  // make sure we show back the cursor, in case the game didn't
  termkit::show_cursor();
  // reset terminal stylings
  std::cout << termkit::DEFAULT_TERM_STYLE;
}
