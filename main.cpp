#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include "includes/hangman.h"
#include "includes/tic.h"
#include "includes/snakes.h"

const char Up = 'W', Down = 'S', Left = 'A', Right = 'D';
const int Dimension = 20;

using namespace std;

void HangMan(int &counter, int &health)
{
    string words[10] = {"pointer", "array", "dynamic", "memory", "debugger", "structure", "recursion", "function", "linux", "programming"};
    vector<char> guessedAlphabets;
    int length, guesses = 0;
    cout << "Welcome to Hangman!" << endl;
    cout << "A random word related to ENGG1340 is selected. You have 7 guesses before you die!" << endl;
    string word = getRandomWord(words, length);
    char *hangman = new char[length];
    for (int i = 0; i < length; i++)
    {
        hangman[i] = word[i];
    }
    cout << "Here is your word: ";
    for (int i = 0; i < length; i++)
    {
        cout << "_";
    }
    cout << endl;
    bool result = getGuesses(hangman, guesses, length, guessedAlphabets);
    endGame(result, word);
    if (!result)
    {
        health -= 40;
    }
    counter++;
    delete[] hangman;
}

/*
    Function Name: WordSearch
    Function Description: Loads puzzle data from text file and allows the player to play the wordsearch game
    Input:
            int health - stores the user's current health
            int counter - stores the user's current counter (number of games completed)
    Output: Prints the puzzles stored in the text file and checks user's answers against answers present in the wordfile
*/
void WordSearch(int &counter, int &health)
{
    // txt file storing the puzzles and answers
    ifstream puzzles("includes/wordsearchpuzzles.txt");

    if (puzzles.fail())
    {
        cout << "Error opening puzzles file.\nPlease proceed to next game :p" << endl;
        counter++;
        return;
    }

    string line;

    vector<string> answers;
    vector<string> userAnswers;

    bool answerPart = false;
    bool puzzleTitle = true;

    while (puzzles >> line)
    {

        if (line == "-----")
        {
            answerPart = true;
        }

        else if (answerPart)
        {
            answers.push_back(line);
        }
        else if (line != "*****")
        {
            for (int i = 0; i < line.length(); i++)
                cout << line[i] << " ";
            cout << endl;
        }

        if (line == "*****")
        {

            answerPart = false;
            int correctAnswers = 0;
            puzzleTitle = true;
            while (correctAnswers < 3)
            {

                cout << "Enter a word (all capital): ";
                string input;
                cin >> input;

                auto found = find(begin(answers), end(answers), input);
                if (found != end(answers))
                {

                    if (find(begin(userAnswers), end(userAnswers), input) != end(userAnswers))
                    {
                        cout << "HOW DARE YOU TRY TO ENTER THE SAME ANSWER AGAIN! TRY AGAIN (booh)" << endl;
                        continue;
                    }

                    userAnswers.push_back(input);

                    cout << "Very good!";
                    correctAnswers++;
                    if (correctAnswers < 3)
                        cout << " You have found " << correctAnswers << " of 3 required words. Find another word" << endl;
                    else
                        cout << endl;
                }

                else
                { // not found
                    cout << "Not one of the answers or not present lol :p" << endl;
                }
            }
            answers.clear();
            userAnswers.clear();
        }
    }
    counter++;
    return;
}

void TicTacToe(int &counter, int &health)
{
    char board[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    printBoard(board);
    cout << endl;
    int turn = 1, index, moves = 0;
    while (!gameOver(board))
    {
        if (moves == 9)
        {
            cout << "DRAW. TRY AGAIN!" << endl;
            for (int i = 0; i < 9; i++)
            {
                board[i] = i + 48;
            }
            printBoard(board);
            cout << endl;
            turn = 1, moves = 0;
        }
        if (turn == 1)
        {
            cout << "Enter Your Move: ";
            cin >> index;
            while (!legitMove(board, index))
            {
                cout << "Invalid Move, Try Again" << endl;
                cout << "Enter Your Move: ";
                cin >> index;
            }
            moves++;
            cout << endl;
            placeMove(board, index, turn);
            printBoard(board);
            cout << endl;
        }
        else
        {
            placeMove(board, nextMove(board), turn);
            moves++;
            cout << "Bosses move:" << endl
                 << endl;
            printBoard(board);
            cout << endl;
        }
        if (turn == 0)
            turn = 1;
        else
            turn = 0;
    }
    switch (turn)
    {
    case 0:
        cout << "Congratulations, you beat the boss! No health is deducted";
        break;
    case 1:
        cout << "You lost! 40 Point is deducted from your health.";
        health -= 40;
    }
    counter++;
}

void SnakesAndLadders(int &counter, int &health)
{
    User one;
    one.player = "P1";
    vector<User> users;
    users.push_back(one);
    string board[100];
    char roll;
    bool gameOver = false;
    int turn = 0;
    makeBoard(board);
    printBoard(board);
    while (!gameOver)
    {
        playerMove(board, users[turn].position, users[turn].prevPosition, users[turn].player);
        printBoard(board);
        if (board[99] == "P1")
        {
            cout << "\nYou won!";
            counter++;
            gameOver = true;
        }
    }
}

/*
    Function Name: RockPaperScissors
    Function Description: Plays a game of rock-paper-scissors with the user till either the user or cpu wins 3 rounds.
    Input:
            int health - stores the user's current health
            int counter - stores the user's current counter (number of games completed)
    Output: Uses standard output to play a simple game of rock-paper-scissors with the user
*/
void RockPaperScissors(int &counter, int &health)
{
    cout << "LET'S PLAY A GAME OF ROCK-PAPER-SCISSORS! FIRST TO 3 WINS!" << endl;

    int userWins = 0, cpuWins = 0; // counter for tracking how many times player has won
    char options[] = {'R', 'P', 'S'};

    while (userWins < 3 && cpuWins < 3)
    {
        char userOption;
        cout << "Choose from R/P/S: ";
        cin >> userOption;

        char cpu = options[rand() % 3];
        cout << "CPU: " << cpu << endl;

        if (userOption == cpu)
        {
            cout << "It's a draw! Let's try again" << endl;
            continue;
        }
        else if ((userOption == 'R' && cpu == 'P') || (userOption == 'P' && cpu == 'S') || (userOption == 'S' && cpu == 'R'))
        {
            cpuWins++;
            cout << "HAHA, I won that. I just need to beat you " << (3 - cpuWins) << " time(s) more." << endl;
        }
        else
        {
            userWins++;
            cout << "You got lucky this time! +1 point for you. Beat me " << (3 - userWins) << " time(s) more." << endl;
        }
    }
    if (userWins == 3)
    {
        cout << "You won!" << endl;
    }
    else
    {
        cout << "HAHA, I win! You lose 20 health points!" << endl;
        health -= 20;
    }
    counter++;
    return;
}

/*
    Function Name: addSymbolsToMaze
    Function Description: Adds special symbols randomly to the generated maze
    Input:  char a[] - Character array storing the generated maze
            vector<int> toAdd - A vector of integers storing the positions of a particular special symbol (games, traps, or health potions)
            vector<int> b, c - Two integer vectors storing the positions of the remaining special symbols
            char Symbol - Character storing the symbol to be randomly added to maze
    Output: Modifies char a[] (maze) and toAdd
*/
void addSymbolsToMaze(char a[Dimension * Dimension], vector<int> &toAdd, vector<int> &b, vector<int> &c, char Symbol)
{
    for (int i = 0; i < 5; i++)
    {
        srand(time(NULL));
        int pos = 1 + (rand() % ((Dimension * Dimension) - 1));
        while (count(toAdd.begin(), toAdd.end(), pos) > 0 || count(b.begin(), b.end(), pos) > 0 || count(c.begin(), c.end(), pos) > 0)
        {
            pos = 1 + (rand() % ((Dimension * Dimension) - 1));
        }
        toAdd.push_back(pos);
        a[pos] = Symbol;
    }
}

/*
    Function Name: makeMaze
    Function Description: Populates the maze with symbols
    Input: char a[] - character array to store the maze
    Output: Modifies char array a by populating with symbols (and calling helper function "addSymbolsToMaze")
*/
void makeMaze(char a[Dimension * Dimension])
{
    vector<int> traps;
    vector<int> health;
    vector<int> levels;
    for (int i = 0; i < Dimension * Dimension; i++)
    {
        a[i] = '#';
    }
    addSymbolsToMaze(a, traps, health, levels, 'T');
    addSymbolsToMaze(a, health, traps, levels, 'H');
    addSymbolsToMaze(a, levels, health, traps, 'G');
}

/*
    Function Name: printMaze
    Function Description: Prints the maze
    Inputs: char a[] - character array which stores the maze
    Output: Prints the contents of maze with proper formatting
*/
void printMaze(char a[Dimension * Dimension])
{
    for (int i = 0; i < Dimension + 1; i++)
    {
        cout << "~ ";
    }
    cout << endl;
    for (int i = 0; i < Dimension * Dimension; i++)
    {
        if (i % Dimension == 0)
        {
            cout << "|" << a[i] << " ";
        }
        else if ((i + 1) % Dimension == 0)
        {
            cout << a[i] << "|" << endl;
        }
        else
        {
            cout << a[i] << " ";
        }
    }
    for (int i = 0; i < Dimension + 1; i++)
    {
        cout << "~ ";
    }
}

/*
    Function Name: landOnSpecialSymbol
    Function Description: Handles the cases when user steps on special symbol
    Input:  char a[] - character array which stores the maze
            char symbol - the symbol the user landed on
            int health - current health of user
            vector<string> games - string vector of playable games
            int counter - counter storing the number of games played by user
    Output: Depending on symbol, performs the required action
*/
void landOnSpecialSymbol(char a[Dimension * Dimension], char symbol, int &health, vector<string> &games, int &counter)
{
    if (symbol == 'T')
    {
        health -= 20;
        cout << "YOU LANDED ON A TRAP, 20 POINTS ARE DEDUCTED FROM YOUR HEALTH";
    }
    else if (symbol == 'H')
    {
        health += 10;
        if (health > 100)
        {
            health = 100;
        }
        cout << "YOU LANDED ON A HEALTH POTION, 10 POINTS ARE ADDED TO YOUR HEALTH";
    }
    else if (symbol == 'G')
    {
        cout << "YOU LANDED ON A GAME, ";
        srand(time(NULL));
        int randomGame = rand() % games.size();
        string gameToPlay = games[randomGame];
        games.erase(games.begin() + randomGame);
        if (gameToPlay == "tic")
        {
            cout << "THE GAME IS: TIC-TAC-TOE" << endl;
            TicTacToe(counter, health);
        }
        else if (gameToPlay == "snakes")
        {
            cout << "THE GAME IS: SNAKES AND LADDERS" << endl;
            SnakesAndLadders(counter, health);
        }
        else if (gameToPlay == "hangman")
        {
            cout << "THE GAME IS: HANGMAN" << endl;
            HangMan(counter, health);
        }
        else if (gameToPlay == "wordsearch")
        {
            cout << "THE GAME IS: WORDSEARCH" << endl;
            WordSearch(counter, health);
        }
        else if (gameToPlay == "rps")
        {
            cout << "THE GAME IS: ROCK-PAPER-SCISSORS" << endl;
            RockPaperScissors(counter, health);
        }
    }
}

/*
    Function Name: SaveGame
    Function Description: Saves the current game status to a txt file
    Input:  char a[] - character array to store the maze
            int pos - stores the user's current position
            int health - stores the user's current health
            int counter - stores the user's current counter (number of games completed)
    Output: Outputs input data to a txt file via ofstream object
*/
void SaveGame(char a[Dimension * Dimension], int pos, int health, int counter, vector<string> &games)
{
    ofstream gameStatus("gamestatus.txt");
    if (gameStatus.fail())
    {
        cout << "ERROR SAVING PROGRESS!" << endl;
        return;
    }
    for (int i = 0; i < (Dimension * Dimension); i++)
        gameStatus << a[i];
    gameStatus << "\n";
    gameStatus << pos << " " << health << " " << counter << " ";
    for (int i = 0; i < games.size(); i++)
        gameStatus << games[i] << " ";
    gameStatus.close();
    cout << "GAME SAVED!" << endl;
    return;
}

/*
    Function Name: LoadGame
    Function Description: Loads the player's progress from a txt file
    Input:  char a[] - character array to store the maze
            int pos - stores the user's current position
            int health - stores the user's current health
            int counter - stores the user's current counter (number of games completed)
            vector<string> games - stores the remaining games
    Output: Processes data in save file and updates the variables accordingly.
*/
bool LoadGame(char a[Dimension * Dimension], int &pos, int &health, int &counter, vector<string> &games)
{
    ifstream gameStatus("gamestatus.txt");
    if (gameStatus.fail())
    {
        cout << "ERROR LOADING SAVE FILE!" << endl;
        return false;
    }
    string maze;
    getline(gameStatus, maze);
    if (maze.length() != (Dimension * Dimension))
    {
        cout << "INVALID SAVE FILE" << endl;
        return false;
    }
    for (int i = 0; i < (Dimension * Dimension); i++)
        a[i] = maze[i];
    gameStatus >> pos >> health >> counter;
    string remainingGames;
    while (gameStatus >> remainingGames)
    {
        games.push_back(remainingGames);
    }
    gameStatus.close();
    return true;
}

/*
    Function Name: movePlayer
    Function Description: Moves the player and updates the concerned data structures accordingly
    Input:  char a[] - character array to store the maze
            int pos - stores the user's current position
            int health - stores the user's current health
            int counter - stores the user's current counter (number of games completed)
    Output: Outputs data to a txt file via ofstream object
*/
bool movePlayer(char a[Dimension * Dimension], string move, int &pos, int &health, vector<string> &games, int &counter, bool &invalid)
{
    invalid = false;
    vector<char> validMoves{'W', 'A', 'S', 'D', 'Q', 'E'};
    int prevPos = pos;
    char prevSymbol = a[prevPos];
    for (int i = 0; i < move.size(); i++)
    {
        if (count(validMoves.begin(), validMoves.end(), move[i]) != 1)
        {
            invalid = true;
            return false;
        }
    }
    for (int i = 0; i < move.size(); i++)
    {
        if (move[i] == Up)
        {
            pos -= Dimension;
            if (pos < 0 || pos >= Dimension * Dimension)
            {
                pos = prevPos;
                return false;
            }
        }
        else if (move[i] == Down)
        {
            pos += Dimension;
            if (pos < 0 || pos >= Dimension * Dimension)
            {
                pos = prevPos;
                return false;
            }
        }
        else if (move[i] == Right)
        {
            pos++;
            if (pos < 0 || pos >= Dimension * Dimension)
            {
                pos = prevPos;
                return false;
            }
        }
        else if (move[i] == Left)
        {
            pos--;
            if (pos < 0 || pos >= Dimension * Dimension)
            {
                pos = prevPos;
                return false;
            }
        }
        else if (move[i] == 'Q')
        {
            SaveGame(a, pos, health, counter, games);
        }
        else if (move[i] == 'E')
        {
            exit(0);
        }
    }
    a[prevPos] = '#';
    char currentSymbol = a[pos];
    a[pos] = 'P';
    landOnSpecialSymbol(a, currentSymbol, health, games, counter);
    return true;
}

int main()
{
    string gameTitle = R""""( _____                           _____ _           ______                                    
|  ___|                         |_   _| |          |  _  \                                   
| |__ ___  ___ __ _ _ __   ___    | | | |__   ___  | | | |_   _ _ __   __ _  ___  ___  _ __  
|  __/ __|/ __/ _` | '_ \ / _ \   | | | '_ \ / _ \ | | | | | | | '_ \ / _` |/ _ \/ _ \| '_ \ 
| |__\__ \ (_| (_| | |_) |  __/   | | | | | |  __/ | |/ /| |_| | | | | (_| |  __/ (_) | | | |
\____/___/\___\__,_| .__/ \___|   \_/ |_| |_|\___| |___/  \__,_|_| |_|\__, |\___|\___/|_| |_|
                   | |                                                 __/ |                 
                   |_|                                                |___/                  )"""";
    cout << gameTitle << endl;
    cout << endl
         << "Welcome! Please choose from the following options below:" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game (your previously saved game)" << endl;
    cout << "3. Exit" << endl;

    int menuChoice;
    cin >> menuChoice;

    if (menuChoice == 3)
    {
        exit(0);
    }

    vector<string> games;
    cout << "YOU HAVE LANDED IN THIS DUNGEON CRAWLER. FINISH ALL THE GAMES WITHOUT LOSING YOUR HEALTH TO ESCAPE." << endl;
    cout << "YOU ARE P, AT THE START OF THE DUNGEON.\nT = TRAP, HEALTH WILL BE DEDUCTED BY 20 IF LANDED ON IT\nH = HEALTH POTIONS, HEALTH WILL INCREASE BY 10 IF LANDED ON IT\nG = GAME, THIS WILL BE A MINIGAME OF SORT THAT YOU HAVE TO FINISH, IF LOST, HEALTH WILL BE DEDUCTED BY 40\n";
    cout << "PRESS " << Up << " TO MOVE UPWARDS BY 1 POSITION" << endl;
    cout << "PRESS " << Left << " TO MOVE LEFT BY 1 POSITION" << endl;
    cout << "PRESS " << Down << " TO MOVE DOWNWARDS BY 1 POSITION" << endl;
    cout << "PRESS " << Right << " TO MOVE RIGHT BY 1 POSITION" << endl;
    cout << "PRESS Q TO SAVE YOUR STATUS. PRESS E TO EXIT THE GAME" << endl;
    cout << "FOR EXAMPLE, IF YOU WANT TO MOVE 3 PLACES RIGHT AND 3 PLACES DOWN, PRESS DDDSSS AND THEN CLICK ENTER\n";
    char maze[Dimension * Dimension];
    bool errorOpeningFile = false;
    int pos = 0, health = 100, counter = 0;
    if (menuChoice == 2)
    {
        if (!LoadGame(maze, pos, health, counter, games))
        {
            cout << "STARTING A NEW GAME INSTEAD" << endl;
            errorOpeningFile = true;
        }
    }
    if (menuChoice == 1 || errorOpeningFile)
    {
        makeMaze(maze);
        maze[0] = 'P';
        pos = 0;
        health = 100;
        counter = 0;
        games.push_back("snakes");
        games.push_back("hangman");
        games.push_back("tic");
        games.push_back("wordsearch");
        games.push_back("rps");
    }

    cout << "\nHEALTH : " << health << endl;
    printMaze(maze);
    bool gameOver = false, invalid = false;

    string gameEnd = R"( _____                        _____                _ 
|  __ \                      |  _  |              | |
| |  \/ __ _ _ __ ___   ___  | | | |_   _____ _ __| |
| | __ / _` | '_ ` _ \ / _ \ | | | \ \ / / _ \ '__| |
| |_\ \ (_| | | | | | |  __/ \ \_/ /\ V /  __/ |  |_|
 \____/\__,_|_| |_| |_|\___|  \___/  \_/ \___|_|  (_)
                                                     
                                                     )";
    while (!gameOver)
    {
        string move;
        cout << "\nENTER YOUR MOVE: ";
        cin >> move;
        while (!movePlayer(maze, move, pos, health, games, counter, invalid))
        {
            if (!invalid)
            {
                cout << "YOU WENT OUT OF THE DUNGEON. ENTER YOUR MOVE AGAIN: ";
            }
            else
            {
                cout << "YOU ENTERED AN INVALID MOVE. ENTER YOUR MOVE AGAIN FROM (W,A,S,D,E,Q) AGAIN: ";
            }
            cin >> move;
        }
        cout << "\nHEALTH : "
             << health << endl;
        printMaze(maze);
        if (health <= 0 || counter == 5)
        {
            gameOver = true;
        }
    }
    cout << endl
         << gameEnd << endl
         << endl;
    if (health <= 0)
    {
        cout << "YOU LOST! BETTER LUCK NEXT TIME" << endl;
    }
    else
    {
        cout << "\nYOU COMPLETED " << counter << "/5 GAMES. YOUR HEALTH IS: " << health << endl;
        cout << "YOU HAVE SUCCESFULLY COMPLETED ALL THE GAMES WITHOUT DYING! YOU ARE OUT OF THE DUNGEON!" << endl;
    }
}
