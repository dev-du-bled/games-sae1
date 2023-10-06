#include "libs/termkit.cpp"

#include <chrono>
#include <thread>

using namespace std;
int main() {
  cout << rgb_fg("rgb_fg(255,0;0)", 255, 0, 0) << endl;
  cout << rgb_bg("rgb_bg(0,255;0)", 0, 255, 0) << endl;
  cout << bold_text("This text is bold") << endl;
  cout << underline_text("This text is underlined") << endl;
  Term_size size;
  size = get_term_size();
  printf("Width: %i\nHeight: %i\n", size.width, size.height);
  cout<<"Hiding cursor in 5 seconds"<<endl;
  hide_cursor();
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  cout<<"Showing cursor"<<endl;
  show_cursor();
  printf("Saving cursor pos\n");
  save_cursor_pos();
  printf("Putting cursor line 3 column 1\n");
  set_cursor_pos(3,2);
  printf("P1\n");
  restore_cursor_pos();
  printf("P2\n");
  
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  clear();
  hide_cursor();
  return 0;
}