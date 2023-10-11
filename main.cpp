#include "libs/termkit.cpp"
#include "games/right price/main.cpp"
#include "games/tictactoe/main.cpp"
#include "games/hanged/main.cpp"
#include "games/pfc/main.cpp"
#include "menu.cpp"

using namespace std;
int main()
{
  showMenu({MenuEntry(&Hangman, "Pendu de FirminGaming"),
            MenuEntry(&justeprix, "Juste prix de Luna"),
            MenuEntry(&tictactoe, "Morpion de Zarox28"),
            MenuEntry(&pfc, "Pierre feuille ciseaux de Dieu")});
  return 0;
}