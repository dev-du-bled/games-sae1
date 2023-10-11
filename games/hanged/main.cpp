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
void DrawHangman(int fail, vector<char> wordByCharGuessed, vector<char> alreadyTested)
{
    termkit::set_term_title("Hangman game");
    termkit::clear();
    termkit::hide_cursor();

    cout << termkit::bold_text(termkit::center_line("-------------- Hangman --------------")) << endl
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

    string wordByCharGuessedString = "";
    for (int i = 0; i < wordByCharGuessed.size(); i++)
    {
        wordByCharGuessedString += wordByCharGuessed[i];
        wordByCharGuessedString += " ";
    }
    string alreadyTestedString = "";
    for (int i = 0; i < alreadyTested.size(); i++)
    {
        alreadyTestedString += alreadyTested[i];
    }

    cout << termkit::center_line("Word: " + wordByCharGuessedString)
         << endl
         << endl;
    if (alreadyTested.size() > 0)
        cout << termkit::center_line("Already used letters: " + alreadyTestedString) << endl;
    cout << endl
         << termkit::bold_text(termkit::center_line("-------------------------------------")) << endl
         << endl;
}

/**
 * @brief Hangman game main function
 */
extern void Hangman()
{
    int fail = 0;               // Number of player's fails
    string word = RandomWord(); // Random word to guess
    bool guessed = false;       // If the player guessed the word
    vector<char> wordByChar,    // Word by char
        wordByCharGuessed;      // Word by char guessed
    vector<char> alreadyTested; // Already tested letters

    for (int i = 0; i < word.length(); i++)
    {
        wordByChar.push_back(word[i]);
        wordByCharGuessed.push_back('_');
    }

    DrawHangman(fail, wordByCharGuessed, alreadyTested);

    while (guessed == false && fail < 9)
    {
        char test = termkit::getch();
        bool alreadyTestedBool = false;

        if (test == 3) // Handle ^C
            return;

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

        DrawHangman(fail, wordByCharGuessed, alreadyTested);
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

    termkit::show_cursor();

    if (guessed == true)
        cout << termkit::center_line("You win !") << endl;
    else
        cout << "     " // When there is bold in text and the text is centered, this space is needed
             << termkit::center_line("You lose ! The word was " + termkit::bold_text(word))
             << endl;
}
