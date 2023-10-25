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

std::string Player::getName()
{
  return name;
}

unsigned char Player::getSymbol()
{
  return symbol;
}

unsigned short Player::getScore()
{
  return score;
}

std::vector<unsigned short> Player::getColor()
{
  return color;
}

void Player::setColor(std::vector<unsigned short> color)
{
  this->color = color;
}

void Player::setName(std::string name)
{
  this->name = name;
}

void Player::setSymbol(char symbol)
{
  this->symbol = symbol;
}

void Player::setScore(unsigned short score)
{
  this->score = score;
}

void Player::addScore()
{
  score++;
}

void Player::resetScore()
{
  score = 0;
}