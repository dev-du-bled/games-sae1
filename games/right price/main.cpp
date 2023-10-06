#include <string>
#include "../../libs/termkit.hpp"
#include <iostream>

class Object {
public:
  std::string name;
  int price;

  Object(std::string name, int price) {
    this->name = name;
    this->price = price;
  }
};

int get_user_input(int min, int max, std::string name) {
  int result;

  std::cout << "Combien pour "
            << termkit::rgb_fg(name, 125, 56, 89) << " ? ("
            << termkit::rgb_fg(std::to_string(min), 24, 103, 255) << " - "
            << termkit::rgb_fg(std::to_string(max), 24, 103, 255) << " )";

  std::cin >> result;
  return result;
}

extern void justeprix() {
  bool won = false;
  int user_guess;
  Object to_guess[1] = {Object("un Awacs", 12)};
  int price_to_guess =  to_guess[0].price;
  
  do {
    user_guess = get_user_input(0, 300, to_guess[0].name);
    if (user_guess < price_to_guess) {
      printf("Higher");
    }
    else if (user_guess > price_to_guess) {
      printf("Lower");
    }
    else {
      won = true;
    }
  } while (!won);
}