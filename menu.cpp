#include "libs/termkit.cpp"
#include "libs/termkit.hpp"
#include <vector>
#include <iostream>

const char *title =R"(
░██████╗███████╗██╗░░░░░███████╗░█████╗░████████╗  ░█████╗░  ░██████╗░░█████╗░███╗░░░███╗███████╗
██╔════╝██╔════╝██║░░░░░██╔════╝██╔══██╗╚══██╔══╝  ██╔══██╗  ██╔════╝░██╔══██╗████╗░████║██╔════╝
╚█████╗░█████╗░░██║░░░░░█████╗░░██║░░╚═╝░░░██║░░░  ███████║  ██║░░██╗░███████║██╔████╔██║█████╗░░
░╚═══██╗██╔══╝░░██║░░░░░██╔══╝░░██║░░██╗░░░██║░░░  ██╔══██║  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░
██████╔╝███████╗███████╗███████╗╚█████╔╝░░░██║░░░  ██║░░██║  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗
╚═════╝░╚══════╝╚══════╝╚══════╝░╚════╝░░░░╚═╝░░░  ╚═╝░░╚═╝  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝)";

extern void menu() {
  termkit::clear();
  std::cout<<termkit::rgb_fg(title, 255, 0, 0)<<std::endl;
}