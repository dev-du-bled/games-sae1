#include <iostream>
#include <string>

extern const char DEFAULT_TERM_STYLE[5] = "\e[0m";

std::string rgb_impl(unsigned r, unsigned g, unsigned b, bool color_background) {
  char buffer[20];
  snprintf(buffer,sizeof(buffer) , "\e[%i;2;%i;%i;%im",(38+color_background*10), r,g,b);
  // Explicit casting from char array to cpp string to avoid being confused
  return (std::string)buffer;
}

extern std::string rgb_fg(unsigned r, unsigned g, unsigned b) {
  return rgb_impl(r,g,b, false);
}

extern std::string rgb_bg(unsigned r, unsigned g, unsigned b) {
  return rgb_impl(r,g,b,true);
}

extern void move_cursor_up(unsigned shift) {
  printf("\e[%iA", shift);  
}
extern void move_cursor_left(unsigned shift) {
  printf("\e[%iD", shift);  
}
extern void move_cursor_right(unsigned shift) {
  printf("\e[%iC", shift);  
}
extern void move_cursor_down(unsigned shift) {
  printf("\e[%iB", shift);  

}
