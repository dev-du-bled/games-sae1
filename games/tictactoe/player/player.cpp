/**
 * @brief This file contains the Player class.
 *
 * @file player.hpp
 *
 * @see player.cpp
 *
 * created by Zarox28
 */

#include "player.hpp"

std::string Player::GetName()
{
  return name;
}

unsigned char Player::GetSymbol()
{
  return symbol;
}

unsigned int Player::GetScore()
{
  return score;
}

std::vector<int> Player::GetColor()
{
  return color;
}

void Player::SetColor(std::vector<int> color)
{
  this->color = color;
}

void Player::SetName(std::string name)
{
  this->name = name;
}

void Player::SetSymbol(char symbol)
{
  this->symbol = symbol;
}

void Player::SetScore(unsigned int score)
{
  this->score = score;
}

void Player::AddScore()
{
  score++;
}

void Player::ResetScore()
{
  score = 0;
}