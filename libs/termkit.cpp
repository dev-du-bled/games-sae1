/**
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
#pragma once

#include "termkit.hpp"
#include <iostream>
#include <string>
#if defined(unix) || defined(__APPLE__)
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#elif defined(_WIN32)
#include <conio.h>
#include <windows.h>
#endif
/* https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
 */
/* https://www.xfree86.org/current/ctlseqs.html */

namespace termkit {
extern const char DEFAULT_TERM_STYLE[5] = "\x1b[0m";

std::string rgb_impl(unsigned r, unsigned g, unsigned b,
                     bool color_background) {
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "\x1b[%i;2;%i;%i;%im",
           (38 + color_background * 10), r, g, b);
  // Explicit casting from char array to cpp string to avoid being confused
  return (std::string)buffer;
}

extern std::string rgb_fg(std::string text, unsigned r, unsigned g,
                          unsigned b) {
  return rgb_impl(r, g, b, false) + text + "\x1b[39m";
}

extern std::string rgb_bg(std::string text, unsigned r, unsigned g,
                          unsigned b) {
  return rgb_impl(r, g, b, true) + text + "\x1b[49m";
}

extern void move_cursor_up(unsigned shift) { printf("\x1b[%iA", shift); }

extern void move_cursor_left(unsigned shift) { printf("\x1b[%iD", shift); }

extern void move_cursor_right(unsigned shift) { printf("\x1b[%iC", shift); }

extern void move_cursor_down(unsigned shift) { printf("\x1b[%iB", shift); }

extern void clear_line() { printf("\x1b[2K"); }

extern void set_term_title(std::string title) {
  printf("\e]2;%s\007", title.c_str());
}

extern std::string bold_text(std::string text) {
  return "\x1b[1m" + text + "\x1b[22m";
}

extern std::string underline_text(std::string text) {
  return "\x1b[4m" + text + "\x1b[24m";
}

extern void save_cursor_pos() { printf("\x1b[s"); }

extern void restore_cursor_pos() { printf("\x1b[u"); }

extern void set_cursor_pos(unsigned line, unsigned column) {
  printf("\x1b[%i;%if\n", line, column);
}

extern void clear() {
  printf("\x1b[2J"); // clears the screen
  printf("\x1b[3J"); // clears the scrollback (history), see (1) clear
  set_cursor_pos(0, 0);
}

#if defined(unix) || defined(__APPLE__)
extern char getch() {
  // TODO: Add windows support
  struct termios original_termios, raw_termios;
  char result;
  // Save original terminal settings
  tcgetattr(STDIN_FILENO, &original_termios);
  // create settings in RawMode
  cfmakeraw(&raw_termios);
  // change to our raw settings
  tcsetattr(STDIN_FILENO, 0, &raw_termios);
  // read one byte into result
  read(STDIN_FILENO, &result, 1);
  // restore original terminal settings
  tcsetattr(STDIN_FILENO, 0, &original_termios);
  return result;
}

#else
extern char getch() { return (char)_getch(); }
#endif

#if defined(unix) || defined(__APPLE__)
extern Term_size get_term_size() {
  struct winsize size;
  Term_size result;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  result.width = size.ws_col;
  result.height = size.ws_row;
  return result;
}


#else
extern Term_size get_term_size() {
  CONSOLE_SCREEN_BUFFER_INFO term_info;
  Term_size result;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &term_info);
  result.width = term_info.dwSize.X;
  result.height = term_info.dwSize.Y;
  return result;
}
#endif

extern void hide_cursor() { printf("\x1b[?25l"); }

extern void show_cursor() { printf("\x1b[?25h"); }

extern std::string center_line(std::string line) {
  std::string result = "";

  Term_size console_size = get_term_size();
  unsigned console_middle_point = console_size.width / 2;
  unsigned text_middle_point = line.length() / 2;

  unsigned center_point = console_middle_point - text_middle_point;
  for (int i = 0; i < center_point; i++) {
    result += " ";
  }
  result += line;
  return result;
}

extern std::string center_text(std::string text) {
  std::string result = "";
  std::string constructed_line = "";

  for (char &character : text) {
    if (character == '\n') {
      result += '\n' + center_line(constructed_line);
      constructed_line = "";
      continue;
    }
    constructed_line += character;
  }
  return result;
}

extern std::string center_text_block(std::string text) {
  std::string result = "";
  std::string constructed_line = "";

  Term_size console_size = get_term_size();
  unsigned console_middle_point = console_size.width / 2;
  unsigned text_middle_point = text.substr(0, text.find('\n')).length() / 2;

  unsigned center_point = console_middle_point - text_middle_point;

  for (auto &character : text) {
    if (character == '\n') {
      result += '\n' + std::string(center_point, ' ') + constructed_line;
      constructed_line = "";
      continue;
    }
    constructed_line += character;
  }
  return result;
}

} // namespace termkit
