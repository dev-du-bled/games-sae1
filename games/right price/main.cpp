/**
 * @brief Juste prix game
 * @file main.cpp
 * @author Luna
 */

#include "../../libs/termkit.hpp"
#include <iostream>
#include <random>
#include <string>
#include "../../libs/utils.hpp"

#define TIME_BEFORE_EXIT 5

// pseudo random number generator using the Mersenne Twister
typedef std::mt19937 RngAlgo;
RngAlgo rng;

/**
 * @brief Generate a random number between min and max
 *
 * @param [in] min Minimum value
 * @param [in] max Maximum value
 *
 * @return int Random number
 */
unsigned random(unsigned min, unsigned max)
{
  rng.seed(time(NULL));
  std::uniform_int_distribution<uint32_t> uint_dist10(min, max);
  return uint_dist10(rng);
}

/**
 * @brief Vitrine minigame, the last one of the show. This is also the game's main function
 *
 * @return void
 */
void justeprix()
{
  unsigned tries = 0;
  unsigned user_input = 0;
  bool found = false;

  termkit::set_term_title("Juste Prix");

  std::cout << termkit::center_line("---------------- Vitrine ----------------") << std::endl;
  std::cout << termkit::center_text("Vous aller devoir trouver le JUSTE PRIX de la vitrine, ça vaut entre 10 000 et 50 000 €,\n parlez clairement, ne vous emballez pas et laisser moi le temps de vous répondre, on y vas ?\n\n") << std::endl;
  std::cout << termkit::center_line(termkit::rgb_bg("  APPUYEZ SUR UNE TOUCHE POUR COMMENCER  ", 255, 192, 203), 42) << std::endl;
  std::cout << std::endl;
  std::cout << termkit::center_line("-----------------------------------------") << std::endl;

  termkit::getch();

  const unsigned price = random(10000, 50000);

  std::string text = "Et c'est partit !";

  while (!found)
  {
    termkit::clear();
    // std::cerr<<price;
    std::cout << termkit::center_line("---------------- Vitrine ----------------") << std::endl;
    std::cout << termkit::center_line(text) << std::endl;
    std::cout << termkit::center_line("Votre prix: ") << std::endl;
    std::cout << termkit::center_line("-----------------------------------------");

    termkit::move_cursor_up(1);
    termkit::move_cursor_left(15);

    std::cin >> user_input;

    tries++;

    if (user_input > price)
    {
      text = termkit::rgb_bg("C'EST MOINS !", 255, 0, 0, true);
    }
    else if (user_input < price)
    {
      text = termkit::rgb_bg("C'EST PLUS !", 173, 216, 230, true);
    }
    else
      break;
  }

  termkit::clear();

  std::cout << termkit::center_line(termkit::rgb_fg("C'EST LE JUSTE PRIX ! La valeur de la vitrine est de '" + std::to_string(price) + "' !", 162, 227, 188, true)) << std::endl;
  std::string tries_str = std::to_string(tries);
  const unsigned visual_string_lenght = tries_str.length() + 33;
  std::cout << termkit::center_line("Vous avez trouve en '" + termkit::rgb_fg(std::to_string(tries), 108, 172, 122) + "' essaies !", visual_string_lenght) << std::endl;

  Utils::wait(5);
}
