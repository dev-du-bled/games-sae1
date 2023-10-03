#include "libs/termkit.cpp"

using namespace std;
int main() {
  cout << rgb_fg("Red text", 255, 0, 0) << endl;
  cout << bold_text("Im the BALLED text, tu du tu du du") << endl;
  cout << underline_text("Underline text") << endl;
  set_term_title("Custom title");
  set_cursor_pos(0, 0);
  printf("X");
  cout << getch();
  struct Term_size ts;
  ts = get_term_size();
  printf("w:%i\nh:%i", ts.width, ts.height);
  return 0;
}