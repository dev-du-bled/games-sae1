/**
 * @brief This file contains the shipwar game
 * @file  main.cpp
 * @author Firmin_
 */

#include <iostream>
#include "../../libs/termkit.cpp"
#include "../../libs/utils.cpp"

using namespace std;

/*
    Ships + Identifiers:
    0 = Water
    1 = Torpedo Boat (2 squares)
    2 = Submarine (3 squares) (2x)
    3 = Cruiser (4 squares)
    4 = Aircraft Carrier (5 squares)
    8 = In water
    9 = Hit
*/

/**
 * @brief Create a string to print the grid on the terminal
 *
 * @param [in] grid Grid to print
 * @param [in] isAnonymous If true, the grid will be anonymized
 *
 * @return Grid in a string
 */
string printGrid(int grid[10][10], bool isAnonymous = false)
{
    string gridString = "";
    for (int i = 0; i < 10; i++)
    {
        gridString += "- - - - - - - - - - - - - - - - - - - - -\n";
        for (int j = 0; j < 10; j++)
        {
            if (j != 0)
                gridString += " ";
            gridString += "| ";

            if (grid[i][j] == 0)
                gridString += termkit::bold_text(" ");
            else if (grid[i][j] == 9)
                gridString += termkit::bold_text("X");
            else if (grid[i][j] == 8)
                gridString += termkit::bold_text("O");
            else if (!isAnonymous)
                gridString += termkit::bold_text(to_string(grid[i][j]));
            else
                gridString += " ";
        }
        gridString += " |";
        gridString += "\n";
    }
    gridString += "- - - - - - - - - - - - - - - - - - - - -\n";
    return gridString;
}

/**
 * @brief Place a ship in the grid
 *
 * @param [in] playerGrid Player grid
 * @param [in] shipLenght Ship lenght
 * @param [in] shipId Ship id
 * @param [in] retry If true, don't redraw the grid
 *
 * @return void
 */
void playerPlaceShip(int playerGrid[10][10], int shipLenght, int shipId, bool retry = false)
{
    if (!retry)
        cout << termkit::center_text_block(printGrid(playerGrid)) << endl;
    cout << termkit::center_line("Entrez sa coordonnée X : ");
    int x;
    cin >> x;
    cout << termkit::center_line("Entrez sa coordonnée Y : ");
    int y;
    cin >> y;
    cout << termkit::center_line("Entrez sa direction (0 = horizontal, 1 = vertical, 2 horizontal-inversé, 3 vertical-inversé) : ");
    int direction;
    cin >> direction;
    bool errorPlacing = false;
    while (direction < 0 || direction > 3)
    {
        cout << termkit::center_line("Erreur de direction !") << endl;
        cout << termkit::center_line("Entrez sa direction (0 = horizontal, 1 = vertical, 2 horizontal-inversé, 3 vertical-inversé) : ");
        cin >> direction;
    }

    if (x < 0 || x > 9 || y < 0 || y > 9)
        errorPlacing = true;
    else if (playerGrid[y][x] != 0)
        errorPlacing = true;
    else
    {
        switch (direction)
        {
        case 0:
            for (int i = 0; i < shipLenght; i++)
            {
                if (playerGrid[y][x + i] != 0 || x + i > 9)
                    errorPlacing = true;
            }
            break;
        case 1:
            for (int i = 0; i < shipLenght; i++)
            {
                if (playerGrid[y + i][x] != 0 || y + i > 9)
                    errorPlacing = true;
            }
            break;
        case 2:
            for (int i = 0; i < shipLenght; i++)
            {
                if (playerGrid[y][x - i] != 0 || x - i < 0)
                    errorPlacing = true;
            }
            break;
        case 3:
            for (int i = 0; i < shipLenght; i++)
            {
                if (playerGrid[y - i][x] != 0 || y - i < 0)
                    errorPlacing = true;
            }
            break;
        default:
            break;
        }
    }
    if (errorPlacing)
    {
        cout << termkit::center_line("Erreur de placement !") << endl;
        playerPlaceShip(playerGrid, shipLenght, shipId, true);
    }
    else
    {
        switch (direction)
        {
        case 0:
            for (int i = 0; i < shipLenght; i++)
            {
                playerGrid[y][x + i] = shipId;
            }
            break;
        case 1:
            for (int i = 0; i < shipLenght; i++)
            {
                playerGrid[y + i][x] = shipId;
            }
            break;
        case 2:

            for (int i = 0; i < shipLenght; i++)
            {
                playerGrid[y][x - i] = shipId;
            }
            break;
        case 3:
            for (int i = 0; i < shipLenght; i++)
            {
                playerGrid[y - i][x] = shipId;
            }
            break;
        default:
            break;
        }
    }
}

/**
 * @brief Place all ships in the grid
 *
 * @param [out] playerGrid Player grid
 *
 * @return void
 */
void playerPlaceShipsInGrid(int playerGrid[10][10])
{
    cout << endl
         << termkit::center_line("Placez vos bateaux !") << endl;
    cout << termkit::center_line("Commencons par placer le Torpilleur (2 cases)") << endl;
    playerPlaceShip(playerGrid, 2, 1);
    termkit::clear();
    cout << termkit::center_line("Placez maintenant le Sous-marin (3 cases)") << endl;
    playerPlaceShip(playerGrid, 3, 2);
    termkit::clear();
    cout << termkit::center_line("Placez maintenant l'autre Sous-marin (3 cases)") << endl;
    playerPlaceShip(playerGrid, 3, 2);
    termkit::clear();
    cout << termkit::center_line("Placez maintenant le Croiseur (4 cases)") << endl;
    playerPlaceShip(playerGrid, 4, 3);
    termkit::clear();
    cout << termkit::center_line("Placez maintenant le Porte-avions (5 cases)") << endl;
    playerPlaceShip(playerGrid, 5, 4);
    termkit::clear();
}

/**
 * @brief Player turn
 *
 * @param [out] otherGrid Other player grid
 *
 * @return void
 */
void playerPlayTurn(int otherGrid[10][10])
{
    cout << termkit::center_text_block(printGrid(otherGrid, true)) << endl;
    cout << termkit::center_line("Entrez sa coordonnée X : ");
    int x;
    cin >> x;
    cout << termkit::center_line("Entrez sa coordonnée Y : ");
    int y;
    cin >> y;
    if (x < 0 || x > 9 || y < 0 || y > 9)
    {
        cout << termkit::center_line("Erreur de coordonnées !") << endl;
        playerPlayTurn(otherGrid);
    }
    else
    {
        if (otherGrid[y][x] == 0)
        {
            cout << termkit::center_line("Dans l'eau !") << endl;
            otherGrid[y][x] = 8;
        }
        else if (otherGrid[y][x] == 9)
        {
            cout << termkit::center_line("Déjà explosé !") << endl;
            playerPlayTurn(otherGrid);
        }
        else
        {
            cout << termkit::center_line("Touché !") << endl;
            otherGrid[y][x] = 9;
        }
    }
}

/**
 * @brief Shipwar game main function
 *
 * @return void
 */
extern void shipwar()
{
    termkit::clear();
    termkit::set_term_title("Bataille navale (1v1)");

    int playerOneGrid[10][10] = {0};
    int playerTwoGrid[10][10] = {0};

    cout << termkit::center_line("Joueur 1, placez vos bateaux !") << endl;
    playerPlaceShipsInGrid(playerOneGrid);
    termkit::clear();
    cout << termkit::center_line("Voici votre grille Joueur 1") << endl;
    cout << termkit::center_text_block(printGrid(playerOneGrid)) << endl;
    Utils::wait(3);
    termkit::clear();

    cout << termkit::center_line("Joueur 2, placez vos bateaux !") << endl;
    playerPlaceShipsInGrid(playerTwoGrid);
    cout << termkit::center_line("Voici votre grille Joueur 2") << endl;
    cout << termkit::center_text_block(printGrid(playerTwoGrid)) << endl;
    Utils::wait(3);
    termkit::clear();

    bool ended = false;
    int playerTurn = 1;

    while (!ended)
    {
        termkit::clear();

        switch (playerTurn)
        {
        case 1:
            cout << termkit::center_line("Joueur 1, c'est à vous !") << endl;
            playerPlayTurn(playerTwoGrid);
            playerTurn = 2;
            break;
        case 2:
            cout << termkit::center_line("Joueur 2, c'est à vous !") << endl;
            playerPlayTurn(playerOneGrid);
            playerTurn = 1;
            break;
        default:
            break;
        }

        ended = true;
        for (int i = 0; i < 10 && ended; ++i)
        {
            for (int j = 0; j < 10 && ended; ++j)
            {
                if (playerOneGrid[i][j] != 0 && playerOneGrid[i][j] != 9)
                {
                    ended = false;
                }
            }
        }

        if (ended)
        {
            cout << termkit::center_line("Le joueur 2 a gagné !") << endl;
            break;
        }

        ended = true;
        for (int i = 0; i < 10 && ended; ++i)
        {
            for (int j = 0; j < 10 && ended; ++j)
            {
                if (playerTwoGrid[i][j] != 0 && playerTwoGrid[i][j] != 9 && playerTwoGrid[i][j] != 8)
                    ended = false;
            }
        }

        if (ended)
        {
            cout << termkit::center_line("Le joueur 1 a gagné !") << endl;
            break;
        }

        Utils::wait(3);
    }
}
