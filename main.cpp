#include "libs/termkit.cpp"

using namespace std;
int main() {
  printf("%sRed text%s\n", rgb_fg(255, 0, 0).c_str(), DEFAULT_TERM_STYLE);
  std::cout << bold_text("Im the BALLED text, tu du tu du du") << std::endl;
  std::cout << underline_text("Underline text") << std::endl;
  set_term_title("Custom title");
  set_cursor_pos(0, 0);
  printf("X");
  return 0;
}