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
#include <string>

namespace termkit {
/**
 * Escape sequence to reset the terminal styling (Removes colors and text
 * effects)
 */
extern const char DEFAULT_TERM_STYLE[5];

class Term_size {
public:
  unsigned width, height;
};

std::string rgb_impl(unsigned r, unsigned g, unsigned b, bool color_background);

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
extern std::string rgb_fg(std::string text, unsigned r, unsigned g, unsigned b);

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
extern std::string rgb_bg(std::string text, unsigned r, unsigned g, unsigned b);

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor up a certain amount of times
 *
 * @param shift How many times to go up
 */
extern void move_cursor_up(unsigned shift);

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor left a certain amount of times
 *
 * @param shift How many times to go left
 */
extern void move_cursor_left(unsigned shift);

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor right a certain amount of times
 *
 * @param shift How many times to go right
 */
extern void move_cursor_right(unsigned shift);

/**
 * Generates a movement escape sequence.
 *
 * Moves the cursor down a certain amount of times
 *
 * @param shift How many times to go down
 */
extern void move_cursor_down(unsigned shift);

/**
 * Clears the line.
 * Moves the cursor at the end of the line.
 */
extern void clear_line();

/**
 * Sets the terminal's window title
 *
 * @param title The new window title
 */
extern void set_term_title(std::string title);

/**
 * Makes the text look THICK
 *
 * @param text Text to be bolded
 */
extern std::string bold_text(std::string text);

/**
 * Draws a line under the text
 *
 * @param text Text to underline
 */
extern std::string underline_text(std::string text);

/**
 * Tells the terminal to save the cursor position for later
 */
extern void save_cursor_pos();

/**
 * Tells the terminal to put the cursor back at the saved position (if any)
 */
extern void restore_cursor_pos();

/**
 * Puts the cursor at coordinate (X,Y)
 * 1,1 is the top left corner
 *
 * @param line Position on the Y axis
 * @param column Position on the X axis
 */
extern void set_cursor_pos(unsigned line, unsigned column);

/**
 * Clears the terminal screen and history
 */
extern void clear();

/**
 * Gets a single char from the user.
 * Does not echo and does not process keys
 */
extern char getch();

/**
 * Gets the size of the terminal in rows and columns
 */
extern Term_size get_term_size();

/**
 * Hide the cursor
 */
extern void hide_cursor();

/**
 * Show the cursor
 */
extern void show_cursor();

/**
 * Centers a single line horizontally
 *
 * Adds space chars for padding
 *
 * @param line String of text to center
 * @return a string padded-left with space chars
 */
extern std::string center_line(std::string line);

/**
 * Centers a paragraph line by line horizontally
 *
 * Calls termkit::center_line en every lines
 *
 * @param text String of text to center
 * @return a string with every line padded-left using space chars
 */
extern std::string center_text(std::string text);

/**
 * Centers a paragraph horizontally
 *
 * @param text String of text to center
 * @return a string with every line padded-left using space chars
 */
extern std::string center_text_block(std::string text);
} // namespace termkit
