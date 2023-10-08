#include <iostream>
#include "dictionary.cpp"
#include "../../libs/termkit.cpp"

using namespace std;

/**
 * @brief Draw the hangman game
 *
 * @param fail Number of fails
 *
 * @param wordByCharGuessed Word by char guessed
 */
void DrawHangman(int fail, char wordByCharGuessed[], int wordLength)
{
    termkit::set_term_title("Hangman game");
    termkit::clear();
    termkit::hide_cursor();

    cout << termkit::center_line("-------------- Hangman --------------") << endl
         << endl;
    vector<std::string> pics = {
        "       \n       \n       \n       \n       \n       \n=========\n",
        "       \n      |\n      |\n      |\n      |\n      |\n=========\n",
        "  +---+\n      |\n      |\n      |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n"};
    cout << termkit::center_text_block(pics[fail]) << endl
         << endl;

    // cout << endl
    //      << termkit::center_text(termkit::bold_text("     Word: "));
    string wordByCharGuessedString = "";
    for (int i = 0; i < wordLength; i++)
    {
        wordByCharGuessedString += wordByCharGuessed[i];
        wordByCharGuessedString += " ";
    }
    cout << termkit::center_line(termkit::bold_text("Word: ") + wordByCharGuessedString) << " " << endl;
    cout << endl
         << termkit::center_line("-------------------------------------") << endl
         << endl;
}

/**
 * @brief Hangman game main function
 */
extern void Hangman()
{
    int fail = 0;                              // Number of player's fails
    string word = RandomWord();                // Random word to guess
    bool guessed = false;                      // If the player guessed the word
    char wordByChar[word.length()] = {},       // Word by char
        wordByCharGuessed[word.length()] = {}; // Word by char guessed
    std::vector<char> alreadyTested;           // Already tested letters

    for (int i = 0; i < word.length(); i++)
    {
        wordByChar[i] = word[i];
        wordByCharGuessed[i] = '_';
    }

    DrawHangman(fail, wordByCharGuessed, word.length());

    while (guessed == false && fail < 9)
    {
        char test = termkit::getch();
        bool alreadyTestedBool = false;

        for (int i = 0; i < alreadyTested.size(); i++)
        {
            if (alreadyTested[i] == test)
            {
                alreadyTestedBool = true;
            }
        }
        if (alreadyTestedBool)
        {
            continue;
        }
        alreadyTested.push_back(test);
        bool found = false;

        for (int i = 0; i < word.length(); i++)
        {
            if (wordByChar[i] == test)
            {
                wordByCharGuessed[i] = test;
                found = true;
            }
        }

        if (found == false)
        {
            fail++;
        }

        DrawHangman(fail, wordByCharGuessed, word.length());
        bool allGuessed = true;

        for (int i = 0; i < word.length(); i++)
        {
            if (wordByCharGuessed[i] == '_')
            {
                allGuessed = false;
            }
        }
        guessed = allGuessed;
    }

    if (guessed == true)
        cout << "You win !" << endl;
    else
        cout << "You lose ! The word was " << word << endl;
}