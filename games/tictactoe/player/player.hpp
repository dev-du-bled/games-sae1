/**
 * @brief This file contains the Player class.
 * @file player.hpp
 * @see player.cpp
 * @author Zarox28
 */

#include <string>

class Player
{
public:
  /**
   * @brief Returns the name of the player
   *
   * @return name of the player
   */
  std::string getName();

  /**
   * @brief Returns the symbol of the player
   *
   * @return symbol of the player
   */
  unsigned char getSymbol();

  /**
   * @brief Returns the score of the player
   *
   * @return score of the player
   */
  unsigned short getScore();

  /**
   * @brief Returns the color of the player
   *
   * @return color of the player
   */
  std::vector<unsigned short> getColor();

  /**
   * @brief Sets the color of the player
   *
   * @param [in] color color of the player
   *
   * @return void
   */
  void setColor(std::vector<unsigned short> color);

  /**
   * @brief Sets the name of the player
   *
   * @param [in] name name of the player
   *
   * @return void
   */
  void setName(std::string name);

  /**
   * @brief Sets the symbol of the player
   * @param [in] symbol symbol of the player
   * @return void
   */
  void setSymbol(char symbol);

  /**
   * @brief Sets the score of the player
   *
   * @param [in] score score of the player
   *
   * @return void
   */
  void setScore(unsigned short score);

  /**
   * @brief Adds 1 to the score of the player
   *
   * @return void
   */
  void addScore();

  /**
   * @brief Resets the score of the player
   *
   * @return void
   */
  void resetScore();

private:
  // ----- ATTRIBUTES -----
  std::string name;
  char symbol;
  unsigned short score;
  std::vector<unsigned short> color;
};