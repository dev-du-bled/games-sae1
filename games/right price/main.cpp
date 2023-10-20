#include "../../libs/termkit.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <time.h>

// pseudo random number generator using the Mersenne Twister
typedef std::mt19937 RngAlgo;
RngAlgo rng;

class Object {
public:
  std::string name;
  unsigned long price;

  Object(std::string name, unsigned long price) {
    this->name = name;
    this->price = price;
  }
};

Object objects[] = {
    Object("AWACS E-3F", 250000000),
    Object("la tablette de Dmitri", 5555),
    Object(
        "un Iphone infinity 5G Pro Max + Ultra Obsidian Titanium Mix Edition",
        2134),
    Object("une Yubikey 5 NFC", 55),
    Object("un casque GAMING", 80),
    Object("un video projecteur", 300),
    Object("une smartwatch", 150),
    Object("une souris GAMING", 60),
    Object("une enceinte Bluetooth", 40),
    Object("un clavier sans fil", 35),
    Object("une chaise de bureau", 120),
    Object("un ordinateur portable", 800),
    Object("un appareil photo", 400),
    Object("un sac à dos de randonnée", 70),
    Object("une machine à café", 50),
    Object("une batterie externe", 25),
    Object("une guitare", 300),
    Object("une imprimante", 150),
    Object("des sneakers", 100),
    Object("un support de tablette", 20),
    Object("des écouteurs", 90),
    Object("une Smart TV", 600),
    Object("une trottinette électrique", 350),
    Object("un drone", 500),
    Object("une table basse", 200),
    Object("un four à micro-ondes", 80),
    Object("un mixeur", 30),
    Object("un aspirateur", 120),
    Object("un grille-pain", 15),
    Object("une lampe de bureau", 40),
    Object("un iso linux", 0),
    Object("une Rubber Ducky", 80),
};

unsigned random(unsigned min, unsigned max) {
  rng.seed(time(NULL));
  std::uniform_int_distribution<uint32_t> uint_dist10(min, max);
  return uint_dist10(rng);
}

void vitrine() {
  bool won = false;
  int user_guess;

  std::string user_input;

  Object object_to_guess = objects[random(0, 30)];
  int price_to_guess = object_to_guess.price;
  std::string object_name = object_to_guess.name;

  do {

    std::cout << "Combien pour " << termkit::rgb_fg(object_name, 125, 56, 89)
              << " ? ";
    std::cin >> user_input;

    // cheat code
    if (user_input == "vincent") {
      break;
    }

    user_guess = std::stoi(user_input);

    if (user_guess < price_to_guess) {
      std::cout << "C'est " + termkit::rgb_fg("plus", 99, 91, 252) + " !"
                << std::endl;
    } else if (user_guess > price_to_guess) {
      std::cout << "C'est " + termkit::rgb_fg("moins", 99, 91, 252) + " !"
                << std::endl;
    } else {
      won = true;
    }
  } while (!won);
  std::cout << "Felicitation !! Vous avez trouvé " +
                   termkit::rgb_fg(std::to_string(price_to_guess), 92, 255,
                                   174) +
                   "€, le prix de " + termkit::rgb_fg(object_name, 92, 255, 174)
            << std::endl;
}

void plus_proche() {}

void trois_part() {}

extern void justeprix() {
  plus_proche();
  trois_part();
  vitrine();
}