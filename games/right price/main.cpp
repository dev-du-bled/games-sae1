#include <string>
#include "../../libs/termkit.cpp"

class Object {
public:
  std::string name;
  int price;

  Object(std::string name, int price) {
    this->name = name;
    this->price = price;
  }
};

int get_user_input(int min, int max, int price) {
  int result;

  std::cout << "Combien pour "
            << rgb_fg(std::to_string(price), 125, 56, 89) << " ? ("
            << rgb_fg(std::to_string(min), 24, 103, 255) << " - "
            << rgb_fg(std::to_string(max), 24, 103, 255) << " )";

  std::cin >> result;
  return result;
}

extern void justeprix() {
  bool won = false;
  int user_guess;
  Object to_guess[1] = {Object("Awacs", 12)};
  int price_to_guess =  to_guess[0].price;
  
  do {
    user_guess = get_user_input(0, 300, price_to_guess);
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