/**
 * @brief This file contains the Player class.
 *
 * @file player.hpp
 *
 * @see player.cpp
 *
 * created by Zarox28
 */

#include <iostream>
#include "../../../libs/termkit.cpp"

#include "player.hpp"

// ----- GETNAME -----
std::string Player::GetName()
{
  return name;
}

// ----- GETSYMBOL -----
unsigned char Player::GetSymbol()
{
  return symbol;
}

// ----- GETSCORE -----
unsigned int Player::GetScore()
{
  return score;
}

// ----- SETNAME -----
void Player::SetName(std::string name)
{
  this->name = name;
}

// ----- SETSYMBOL -----
void Player::SetSymbol(unsigned char symbol)
{
  this->symbol = symbol;
}

// ----- SETSCORE -----
void Player::SetScore(unsigned int score)
{
  this->score = score;
}

// ----- ADDSCORE -----
void Player::AddScore()
{
  score++;
}

// ----- RESETSCORE -----
void Player::ResetScore()
{
  score = 0;
}