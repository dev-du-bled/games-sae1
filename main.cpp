#include "libs/termkit.cpp"
#include "games/right price/main.cpp"
#include "games/tictactoe/main.cpp"
#include "games/hanged/main.cpp"
#include "games/pfc/main.cpp"
#include "games/shipwar/main.cpp"
#include "games/reflex/main.cpp"
#include "menu.cpp"

using namespace std;
int main()
{
  showMenu({MenuEntry(&Hangman, "Pendu de FirminGaming"),
            MenuEntry(&justeprix, "Juste prix de Luna"),
            MenuEntry(&tictactoe, "Morpion de Zarox28"),
            MenuEntry(&pfc, "Gravier Carton Couteau de Dieu"),
            MenuEntry(&shipwar, "Bataille navale de BoomTchaGong"),
            MenuEntry(&reflex, "Jeu de reflex de Zarox28")});
  
  // make sure we show back the cursor, in case the game didn't
  termkit::show_cursor();
  // reset terminal stylings
  std::cout << termkit::DEFAULT_TERM_STYLE;
  return 0;
}