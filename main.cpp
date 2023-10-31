#include "games/right price/main.cpp"
#include "games/tictactoe/main.cpp"
#include "games/hanged/main.cpp"
#include "games/gcc/main.cpp"
#include "games/shipwar/main.cpp"
#include "games/reflex/main.cpp"
#include "games/connect4/main.cpp"
#include "libs/termkit.hpp"
#include "menu.cpp"



using namespace std;
int main()
{
  termkit::handle_SIGINT();
  cout<<"\x1b[?47h"; // switch to alternative buffer if available
  showMenu({MenuEntry(&Hangman, "Pendu de FirminGaming"),
            MenuEntry(&justeprix, "Juste prix de Luna"),
            MenuEntry(&tictactoe, "Morpion de Zarox28"),
            MenuEntry(&pfc, "Gravier Carton Couteau de Dieu"),
            MenuEntry(&shipwar, "Bataille navale de BoomTchaGong"),
            MenuEntry(&reflex, "Jeu de reflex de Zarox28"),
            MenuEntry(&connect4, "Puissance 4 de stereo18")});

  // make sure we show back the cursor, in case the game didn't
  termkit::show_cursor();
  // reset terminal stylings
  std::cout << termkit::DEFAULT_TERM_STYLE;
  cout<<"\x1b[?47l"; // switch to normal buffer if available
  return 0;
}
