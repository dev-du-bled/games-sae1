#include "libs/termkit.hpp"
#include <iostream>
#include <random>

const char *title =
    R"( _____ _____ _      _____ _____ _____    ___    _____   ___  ___  ___ _____ 
/  ___|  ___| |    |  ___/  __ \_   _|  / _ \  |  __ \ / _ \ |  \/  ||  ___|
\ `--.| |__ | |    | |__ | /  \/ | |   / /_\ \ | |  \// /_\ \| .  . || |__  
 `--. \  __|| |    |  __|| |     | |   |  _  | | | __ |  _  || |\/| ||  __| 
/\__/ / |___| |____| |___| \__/\ | |   | | | | | |_\ \| | | || |  | || |___ 
\____/\____/\_____/\____/ \____/ \_/   \_| |_/  \____/\_| |_/\_|  |_/\____/
)";

extern void menu() {
  termkit::clear();
  std::cout << termkit::rgb_fg(termkit::center_text_block(title), 255, 0, 0) << std::endl;
  std::cout << termkit::center_line(std::string(52, ' ') + termkit::bold_text("v0.0.1"))<<std::endl;
  std::cout<<termkit::center_text(R"(
CENTERED
TEXT      
)");
}
