/**
 * This file contains the Player class.
 *
 * @file player.hpp
 *
 * @see player.cpp
 *
 * created by Zarox28
 */

#include <string>

class Player
{
public:
  /**
   * @brief Returns the name of the player
   *
   * @return name of the player
   *
   */
  std::string GetName();

  /**
   * @brief Returns the symbol of the player
   *
   * @return symbol of the player
   *
   */
  unsigned char GetSymbol();

  /**
   * @brief Returns the score of the player
   *
   * @return score of the player
   *
   */
  unsigned int GetScore();

  /**
   * @brief Sets the name of the player
   *
   * @param name name of the player
   *
   * @return void
   */
  void SetName(std::string name);

  /**
   * @brief Sets the symbol of the player
   *
   * @param symbol symbol of the player
   *
   * @return void
   */
  void SetSymbol(char symbol);

  /**
   * @brief Sets the score of the player
   *
   * @param score score of the player
   *
   * @return void
   */
  void SetScore(unsigned int score);

  /**
   * @brief Adds 1 to the score of the player
   *
   * @return void
   */
  void AddScore();

  /**
   * @brief Resets the score of the player
   *
   * @return void
   */
  void ResetScore();

private:
  // ----- ATTRIBUTES -----
  std::string name;
  char symbol;
  unsigned int score;
};