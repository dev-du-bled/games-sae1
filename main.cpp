#include "libs/termkit.cpp"
#include "games/right price/main.cpp"
#include "games/hanged/main.cpp"
#include "menu.cpp"

using namespace std;
int main() {
  showMenu({
    MenuEntry(&Hangman, "Pendu de FirminGaming"),
    MenuEntry(&justeprix, "Juste prix de Luna")
  });
  return 0;
}