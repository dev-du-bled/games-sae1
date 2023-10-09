#include "libs/termkit.hpp"
#include <iostream>
#include <random>
#include <vector>

const char *title =
    R"( _____ _____ _      _____ _____ _____    ___    _____   ___  ___  ___ _____ 
/  ___|  ___| |    |  ___/  __ \_   _|  / _ \  |  __ \ / _ \ |  \/  ||  ___|
\ `--.| |__ | |    | |__ | /  \/ | |   / /_\ \ | |  \// /_\ \| .  . || |__  
 `--. \  __|| |    |  __|| |     | |   |  _  | | | __ |  _  || |\/| ||  __| 
/\__/ / |___| |____| |___| \__/\ | |   | | | | | |_\ \| | | || |  | || |___ 
\____/\____/\_____/\____/ \____/ \_/   \_| |_/  \____/\_| |_/\_|  |_/\____/
)";

class MenuEntry {
public:
  void (*callee)();
  std::string dislayName;

  MenuEntry(void (*callee)(), std::string name) {
    this->callee = callee;
    this->dislayName = name;
  }
};

extern void showMenu(std::vector<MenuEntry> games) {
  unsigned short selected_option = 0;
  bool is_selecting = true;

  termkit::clear();
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
        std::cout << termkit::rgb_fg(termkit::center_line(games[i].dislayName),255, 0, 0)
                  << std::endl;
      } else
        std::cout << termkit::center_line(games[i].dislayName) << std::endl;
    }
    termkit::move_cursor_up(games.size());

    // keyboard input
    char g = termkit::getch();
    switch (g) {
    case 3:
      return;
    case 9:
      selected_option = (selected_option + 1) % games.size();
      continue;
    case 13:
      is_selecting = false;
      break;
    }
  }
  games[selected_option].callee();
}
