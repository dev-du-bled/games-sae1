#include "libs/termkit.cpp"

int main()
{
    printf("%sRed text%s", rgb_fg(255,0,0).c_str(), DEFAULT_TERM_STYLE);
    move_cursor_left(5);
    std::cout<<"ehehehh";
    return 0;
}