/* 
 * This file is part of the Luna distribution (https://github.com/0x454d505459).
 * Copyright (c) 2023 Luna OGER--MASSICOT.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
