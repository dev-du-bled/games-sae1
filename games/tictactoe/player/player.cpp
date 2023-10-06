#include <iostream>
#include "../../../libs/termkit.cpp"

#include "player.hpp"

// ----- GETNAME -----
std::string Player::GetName() {
  return name;
}

// ----- GETSYMBOL -----
unsigned char Player::GetSymbol() {
  return symbol;
}

// ----- GETSCORE -----
unsigned int Player::GetScore() {
  return score;
}

// ----- SETNAME -----
void Player::SetName(std::string name) {
  this->name = name;
}

// ----- SETSYMBOL -----
void Player::SetSymbol(unsigned char symbol) {
  this->symbol = symbol;
}