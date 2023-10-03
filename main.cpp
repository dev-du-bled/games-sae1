#include "libs/termkit.cpp"

using namespace std;
int main() {
  printf("%sRed text%s", rgb_fg(255, 0, 0).c_str(), DEFAULT_TERM_STYLE);
  move_cursor_left(5);
  cout << "Lorem ipsum dolor sit ammet";
  clear_line();
  cout << "He" << endl;
  return 0;
}