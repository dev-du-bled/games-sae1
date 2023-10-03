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
#include <termios.h>
#include <unistd.h>
/* https://www.xfree86.org/current/ctlseqs.html */

/**
 * Escape sequence to reset the terminal styling (Removes colors and text
 * effects)
 */
extern const char DEFAULT_TERM_STYLE[5] = "\e[0m";

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
  snprintf(buffer, sizeof(buffer), "\e[%i;2;%i;%i;%im",
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
  return rgb_impl(r, g, b, false) + text + "\e[39m";
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
  return rgb_impl(r, g, b, true) + text + "\e[49m";
}

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor up a certain amount of times
 *
 * @param shift How many times to go up
 */
extern void move_cursor_up(unsigned shift) { printf("\e[%iA", shift); }

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor left a certain amount of times
 *
 * @param shift How many times to go left
 */
extern void move_cursor_left(unsigned shift) { printf("\e[%iD", shift); }

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor right a certain amount of times
 *
 * @param shift How many times to go right
 */
extern void move_cursor_right(unsigned shift) { printf("\e[%iC", shift); }

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor down a certain amount of times
 *
 * @param shift How many times to go down
 */
extern void move_cursor_down(unsigned shift) { printf("\e[%iB", shift); }

/**
 * Clears the line.
 * Moves the cursor at the end of the line.
 */
extern void clear_line() { printf("\e[2K"); }

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
  return "\e[1m" + text + "\e[22m";
}

/**
 * Draws a line under the text
 *
 * @param text Text to underline
 */
extern std::string underline_text(std::string text) {
  return "\e[4m" + text + "\e[24m";
}

/**
 * Tells the terminal to save the cursor position for later
 */
extern void save_cursor_pos() { printf("\e[s"); }

/**
 * Tells the terminal to put the cursor back at the saved position (if any)
 */
extern void restore_cursor_pos() { printf("\e[u"); }

/**
 * Puts the cursor at coordinate (X,Y)
 *
 * 0,0 is the top left corner
 *
 * @param x Position on the X axis
 * @param y Position on the Y axis
 */
extern void set_cursor_pos(unsigned x, unsigned y) {
  printf("\e[%i;%if\n", x, y);
}

/**
 * Clears the terminal screen and history
 */
extern void clear() {
  printf("\e[2J"); // clears the screen
  printf("\e[3J"); // clears the scrollback (history), see (1) clear
  set_cursor_pos(0, 0);
}

/**
 * Gets a single char from the user.
 * Does not echo and does not process keys 
 */
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
/**
 * An alternative way to clear the screen
 */
extern void clear_alternative() { printf("\e[f"); }
