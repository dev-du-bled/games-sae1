/**
 * @brief This file contains the Connect4 (Also known as *Puissance 4*) game
 * @file  main.cpp
 * @author Firmin_
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include "../../libs/termkit/termkit.cpp"
#include "../../libs/utils.cpp"

using namespace std;

/**
 * @brief Draw the Connect 4 grid only
 *
 * @param [in] grid The grid to draw
 * @param [in] cursorPos The cursor position
 */
void drawConnect4Grid(int grid[6][7], int cursorPos)
{
    std::stringstream l1;
    l1 << std::setw(cursorPos * 2) << ""
       << "| " << std::setw((7 - cursorPos) * 2) << "";
    std::cout << termkit::center_line(l1.str()) << std::endl;
    std::stringstream l2;
    l2 << std::setw(cursorPos * 2) << ""
       << "V " << std::setw((7 - cursorPos) * 2) << "";
    std::cout << termkit::center_line(l2.str()) << std::endl;

    cout << termkit::center_line("---------------") << endl;
    for (int i = 0; i < 6; i++)
    {
        string line = "|";
        for (int j = 0; j < 7; j++)
        {
            switch (grid[i][j])
            {
            case 0:
                line += " ";
                break;
            case 1:
                line += "X";
                break;
            case 2:
                line += "O";
                break;
            default:
                line += "E";
                break;
            }
            line += "|";
        }
        cout << termkit::center_line(line) << endl;
    }
    cout << termkit::center_line("---------------") << endl;
}

/**
 * @brief Draw the Connect 4 game
 *
 * @param [in] grid The game grid to draw
 * @param [in] cursorPos The cursor position
 * @param [in] playerTurn The player who's turn it is
 */
void drawConnect4(int grid[6][7], int cursorPos, int playerTurn)
{
    termkit::clear();
    cout << termkit::center_line("---------------------- Connect 4 ----------------------") << endl
         << endl;
    cout << termkit::center_line("Player'" + to_string(playerTurn) + "s turn") << endl;
    drawConnect4Grid(grid, cursorPos);
    cout << termkit::center_line("Press the left and right arrow keys to move the cursor") << endl;
    cout << termkit::center_line("Press enter to place a token") << endl
         << endl;
    cout << termkit::center_line("-------------------------------------------------------") << endl;
}

/**
 * @brief Chech if there is a connect 4 in the grid
 *
 * @param [in] grid The grid to check
 * @return The player who won, 0 if no one won
 */
int checkConnect4(int grid[6][7])
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++) // Horizontal
        {
            int player = grid[i][j];
            if (player != 0 && player == grid[i][j + 1] && player == grid[i][j + 2] && player == grid[i][j + 3])
                return player;
        }
        if (i < 3)
        {
            for (int j = 0; j < 7; j++) // Vertical
            {
                int player = grid[i][j];
                if (player != 0 && player == grid[i + 1][j] && player == grid[i + 2][j] && player == grid[i + 3][j])
                    return player;
            }
            for (int j = 3; j < 7; j++) // Diagonal left
            {
                int player = grid[i][j];
                if (player != 0 && player == grid[i + 1][j - 1] && player == grid[i + 2][j - 2] && player == grid[i + 3][j - 3])
                    return player;
            }
            for (int j = 0; j < 4; j++) // Diagonal right
            {
                int player = grid[i][j];
                if (player != 0 && player == grid[i + 1][j + 1] && player == grid[i + 2][j + 2] && player == grid[i + 3][j + 3])
                    return player;
            }
        }
    }
    return 0;
}

/**
 * @brief Connect 4 game main function
 */
extern void connect4()
{
    termkit::set_term_title("Connect 4");

    int grid[6][7] = {0};
    int playerTurn = 1;
    int cusorPos = 1;
    int winner = 0;

    drawConnect4(grid, cusorPos, playerTurn);
    while (winner == 0)
    {
#if defined(unix) || defined(__APPLE__) // linux and mac support
        int leftArrow = 68;
        int rightArrow = 67;
#elif defined(_WIN32) || defined(_WIN64) // windows support
        int leftArrow = 75;
        int rightArrow = 77;
#endif
        int usrInput = termkit::getch();
        if (usrInput == leftArrow && cusorPos > 1) // Left arrow
            cusorPos--;
        else if (usrInput == rightArrow && cusorPos < 7) // Right arrow
            cusorPos++;
        else if (usrInput == 13) // Enter
        {
            int i = 0;
            while (i < 6 && grid[i][cusorPos - 1] == 0) // Find the first used slot from the bottom
                i++;
            if (i > 0)
            {
                grid[i - 1][cusorPos - 1] = playerTurn; // Place the token (i-1 because i is obviously used and cursorPos-1 because the grid starts at 0 but the cursor starts at 1)
                if (playerTurn == 1)
                    playerTurn = 2;
                else
                    playerTurn = 1;
            }
        }
        else if (usrInput == 3) // Ctrl^C
            return;
        drawConnect4(grid, cusorPos, playerTurn);
        winner = checkConnect4(grid);
    }
    cout << termkit::center_line("Player " + to_string(winner) + " won !") << endl;
    Utils::wait(5);
}