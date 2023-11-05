#include "games/right price/main.cpp"
#include "games/tictactoe/main.cpp"
#include "games/hanged/main.cpp"
#include "games/gcc/main.cpp"
#include "games/shipwar/main.cpp"
#include "games/reflex/main.cpp"
#include "games/connect4/main.cpp"
#include "libs/termkit/termkit.cpp"
#include "menu.cpp"

using namespace std;
int main()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  SetConsoleOutputCP(CP_UTF8); // Enable UTF-8 support for Windows console because it's 2023 and it's still not enabled by default
#endif
  termkit::handle_SIGINT();
  cout << "\x1b[?47h"; // switch to alternative buffer if available
  showMenu({MenuEntry(&Hangman, "Pendu de Firmin"),
            MenuEntry(&justeprix, "Juste prix de Gabriel"),
            MenuEntry(&tictactoe, "Morpion d'Alexian"),
            MenuEntry(&pfc, "Gravier Carton Couteau™ de Firmin"),
            MenuEntry(&shipwar, "Bataille navale de Firmin"),
            MenuEntry(&reflex, "Jeu de reflex d'Alexian"),
            MenuEntry(&connect4, "Puissance 4 de Firmin")});

  // make sure we show back the cursor, in case the game didn't
  termkit::show_cursor();
  // reset terminal stylings
  std::cout << termkit::DEFAULT_TERM_STYLE;
  cout << "\x1b[?47l"; // switch to normal buffer if available
  return 0;
}
