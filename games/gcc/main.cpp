/**
 * @brief This file contains the Gravier Carton Couteau™ game
 * @file  main.cpp
 * @author Firmin_
 */

#include <iostream>
#include "../../libs/termkit/termkit.cpp"
#include "../../libs/utils.cpp"

using namespace std;

/**
 * @brief Generate a random hand between 0 and 2.
 *
 * @return int 0 for Gravier, 1 for Carton, 2 for Couteau
 */
int randomHand()
{
    srand(time(0));
    return rand() % 3;
}

/**
 * @brief Compare two plays and return the winner
 *
 * @param [in] playOne Player's play
 * @param [in] playTwo Computer's play
 *
 * @return int 0 if draw, 1 if player one, 2 if computer won
 */
int ComparePlays(int playOne, int playTwo)
{
    if (playOne == playTwo)
        return 0;
    else if (playOne == 0)
    {
        if (playTwo == 1)
            return 2;
        else
            return 1;
    }
    else if (playOne == 1)
    {
        if (playTwo == 0)
            return 1;
        else
            return 2;
    }
    else if (playOne == 2)
    {
        if (playTwo == 0)
            return 2;
        else
            return 1;
    }
    else
        return 0;
}

/**
 * @brief Draw the Gravier Carton Couteau™ game in terminal
 *
 * @param [in] mode 0 if the player hasn't played, 1 if the player has played
 * @param [in] playerScore Player score
 * @param [in] computerScore Computer score
 * @param [in] rounds Number of rounds
 * @param [in] win 0 if draw, 1 if player one, 2 if computer won
 * @param [in] playerPlay Player's play
 * @param [in] computerPlay Computer's play
 *
 * @return void
 */
void DrawPfc(int mode, int playerScore, int computerScore, int roundsPlayed, int rounds, int win = 0, int playerPlay = 0, int computerPlay = 0)
{
    termkit::set_term_title("Gravier Carton Couteau");
    termkit::clear();
    termkit::hide_cursor();

    string hands[3] = {
        "    _______\n---'   ____)\n      (_____)\n      (_____)\n      (____)\n---.__(___)\n",                          // Gravier hand
        "     _______\n---'    ____)____\n           ______)\n          _______)\n         _______)\n---.__________)\n", // Carton hand
        "    _______\n---'   ____)____\n          ______)\n       __________)\n      (____)\n---.__(___)\n"};            // Couteau hand

    cout
        << termkit::bold_text(termkit::center_line("-------------- Gravier Carton Couteau (" + to_string(roundsPlayed) + "/" + to_string(rounds) + ") --------------")) << endl
        << endl;
    switch (mode)
    {
    case 0: // If the player hasn't played
        cout << termkit::center_line("Choisir une main :") << endl;
        cout << termkit::center_text_block("1. Gravier\n2. Carton\n3. Couteau\n") << endl;
        break;
    case 1: // If the player has played
        cout << termkit::center_line("Votre main");
        cout << termkit::center_text_block(hands[playerPlay]) << endl
             << endl
             << endl;
        cout << termkit::center_line("Main de l'ordinateur");
        cout << termkit::center_text_block(hands[computerPlay]) << endl
             << endl;
        switch (win)
        {
        case 0:
            cout
                << termkit::center_line("Egalité !") << endl;
            break;
        case 1:
            cout
                << termkit::center_line("Vous avez gagné !") << endl;
            break;
        case 2:
            cout
                << termkit::center_line("Vous avez perdu !") << endl;
            break;
        default:
            break;
        }
        break;
    }
    cout
        << endl
        << termkit::center_line("Vous : " + to_string(playerScore)) << endl
        << termkit::center_line("Ordinateur : " + to_string(computerScore)) << endl;
    cout << endl
         << termkit::bold_text(termkit::center_line("----------------------------------------------------------")) << endl;
}

/**
 * @brief Gravier Carton Couteau™ game main function
 *
 * @return void
 */
extern void pfc()
{
    int rounds = 0;        // Number of rounds
    int roundsPlayed = 0;  // Number of rounds played
    int playerScore = 0;   // Player score
    int computerScore = 0; // Computer score

    while (rounds > 10 || rounds < 1)
    {
        cout << endl
             << termkit::center_line("Nombre de manches (1-10) : ");
        cin >> rounds;
    }

    for (int i = 0; i < rounds; i++)
    {
        DrawPfc(0, playerScore, computerScore, roundsPlayed, rounds);
        int playerPlay = -1;
        while (playerPlay != 0 && playerPlay != 1 && playerPlay != 2)
        {
            char playPlayChar = termkit::getch();
            switch (playPlayChar)
            {
            case '1':
                playerPlay = 0;
                break;
            case '2':
                playerPlay = 1;
                break;
            case '3':
                playerPlay = 2;
                break;
            case 3: // Handle ^C
                return;
            default:
                playerPlay = -1;
                break;
            }
        }

        int computerPlay = randomHand();
        int winner = ComparePlays(playerPlay, computerPlay);
        switch (winner)
        {
        case 1:
            playerScore++;
            break;
        case 2:
            computerScore++;
            break;
        default:
            break;
        }
        roundsPlayed++;
        DrawPfc(1, playerScore, computerScore, roundsPlayed, rounds, winner, playerPlay, computerPlay);
        Utils::wait(3);
    }
    if (playerScore == computerScore)
        cout << endl
             << termkit::center_line("Egalité du match !") << endl;
    else if (playerScore > computerScore)
        cout << endl
             << termkit::center_line("Vous avez gagné le match !") << endl;
    else
        cout << endl
             << termkit::center_line("Vous avez perdu le match !") << endl;
    Utils::wait(5);
}