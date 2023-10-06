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
#if defined(unix)
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#elif defined(_win32)
#include <windows.h>
#endif
/* https://www.xfree86.org/current/ctlseqs.html */

/**
 * Escape sequence to reset the terminal styling (Removes colors and text
 * effects)
 */
extern const char DEFAULT_TERM_STYLE[5] = "\x1b[0m";

class Term_size {
public:
  int width, height;
};

/**
 * Generates a color escape sequence.
 *
 * This is the implementation behind rgb_fg and rgb_bg; it isn't meant
 * to be used by any functions other than rgb_fg and rgb_bg.
 *
 * @see rgb_fg and rgb_bg for usable functions
 *
 * @param r Intensity of the red channel (ranges from 0-255)
 * @param g Intensity of the green channel (ranges from 0-255)
 * @param b Intensity of the blue channel (ranges from 0-255)
 * @param color_background To use the color for background coloring or not
 * @return color ANSI Escape sequence representing a color
 */
std::string rgb_impl(unsigned r, unsigned g, unsigned b,
                     bool color_background) {
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "\x1b[%i;2;%i;%i;%im",
           (38 + color_background * 10), r, g, b);
  // Explicit casting from char array to cpp string to avoid being confused
  return (std::string)buffer;
}

/**
 * Generates a color escape sequence.
 *
 * Colors the foreground with the given color
 *
 * @param r Intensity of the red channel (ranges from 0-255)
 * @param g Intensity of the green channel (ranges from 0-255)
 * @param b Intensity of the blue channel (ranges from 0-255)
 * @return color ANSI Escape sequence representing a color
 */
extern std::string rgb_fg(std::string text, unsigned r, unsigned g,
                          unsigned b) {
  return rgb_impl(r, g, b, false) + text + "\x1b[39m";
}

/**
 * Generates a color escape sequence.
 *
 * Colors the background with the given color
 *
 * @param r Intensity of the red channel (ranges from 0-255)
 * @param g Intensity of the green channel (ranges from 0-255)
 * @param b Intensity of the blue channel (ranges from 0-255)
 * @return color ANSI Escape sequence representing a color
 */
extern std::string rgb_bg(std::string text, unsigned r, unsigned g,
                          unsigned b) {
  return rgb_impl(r, g, b, true) + text + "\x1b[49m";
}

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor up a certain amount of times
 *
 * @param shift How many times to go up
 */
extern void move_cursor_up(unsigned shift) { printf("\x1b[%iA", shift); }

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor left a certain amount of times
 *
 * @param shift How many times to go left
 */
extern void move_cursor_left(unsigned shift) { printf("\x1b[%iD", shift); }

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor right a certain amount of times
 *
 * @param shift How many times to go right
 */
extern void move_cursor_right(unsigned shift) { printf("\x1b[%iC", shift); }

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor down a certain amount of times
 *
 * @param shift How many times to go down
 */
extern void move_cursor_down(unsigned shift) { printf("\x1b[%iB", shift); }

/**
 * Clears the line.
 * Moves the cursor at the end of the line.
 */
extern void clear_line() { printf("\x1b[2K"); }

/**
 * Sets the terminal's window title
 *
 * @param title The new window title
 */
extern void set_term_title(std::string title) {
  printf("\e]2;%s\007", title.c_str());
}

/**
 * Makes the text look THICK
 *
 * @param text Text to be bolded
 */
extern std::string bold_text(std::string text) {
  return "\x1b[1m" + text + "\x1b[22m";
}

/**
 * Draws a line under the text
 *
 * @param text Text to underline
 */
extern std::string underline_text(std::string text) {
  return "\x1b[4m" + text + "\x1b[24m";
}

/**
 * Tells the terminal to save the cursor position for later
 */
extern void save_cursor_pos() { 
 printf("\x1b[s"); 
}

/**
 * Tells the terminal to put the cursor back at the saved position (if any)
 */
extern void restore_cursor_pos() { printf("\x1b[u"); }

/**
 * Puts the cursor at coordinate (X,Y)
 * 1,1 is the top left corner
 *
 * @param line Position on the Y axis
 * @param column Position on the X axis
 */
extern void set_cursor_pos(unsigned line, unsigned column) {
  printf("\x1b[%i;%if\n", line, column);
}

/**
 * Clears the terminal screen and history
 */
extern void clear() {
  printf("\x1b[2J"); // clears the screen
  printf("\x1b[3J"); // clears the scrollback (history), see (1) clear
  set_cursor_pos(0, 0);
}

/**
 * Gets a single char from the user.
 * Does not echo and does not process keys
 */
#if defined(unix)
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
#endif
/**
 * Gets the size of the terminal in rows and columns
 */
extern Term_size get_term_size() {
#if defined(unix)
  struct winsize size;
  Term_size result;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  result.width = size.ws_col;
  result.height = size.ws_row;
  return result;
#elif defined(_win32)
  CONSOLE_SCREEN_BUFFER_INFO term_info;
  Term_size result;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &term_info);
  result.width = term_info.srWindow.Right - term_info.srWindow.Left + 1;
  result.height = term_info.srWindow.Bottom - term_info.srWindow.Top + 1;
  return result;
#endif
}

/**
 * Hide the cursor
 */
extern void hide_cursor() {
  printf("\x1b[?25l");
}

/**
 * Show the cursor
 */
extern void show_cursor() {
  printf("\x1b[?25h");
}

/**
 * An alternative way to clear the screen
 */
extern void clear_alternative() { printf("\x1b[f"); }
