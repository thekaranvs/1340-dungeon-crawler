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
    if (result)
    {
        counter++;
    }
    else
    {
        health -= 40;
    }
    delete[] hangman;
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
        counter++;
        break;
    case 1:
        cout << "You lost! 40 Point is deducted from your health.";
        health -= 40;
    }
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
        string gameToPlay = games[games.size() - 1];
        games.pop_back();
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
    }
}

bool movePlayer(char a[Dimension * Dimension], string move, int &pos, int &health, vector<string> &games, int &counter)
{
    int prevPos = pos;
    char prevSymbol = a[prevPos];
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
        if (move[i] == Down)
        {
            pos += Dimension;
            if (pos < 0 || pos >= Dimension * Dimension)
            {
                pos = prevPos;
                return false;
            }
        }
        if (move[i] == Right)
        {
            pos++;
            if (pos < 0 || pos >= Dimension * Dimension)
            {
                pos = prevPos;
                return false;
            }
        }
        if (move[i] == Left)
        {
            pos--;
            if (pos < 0 || pos >= Dimension * Dimension)
            {
                pos = prevPos;
                return false;
            }
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
    vector<string> games;
    games.push_back("snakes");
    games.push_back("hangman");
    games.push_back("tic");
    cout << "YOU HAVE LANDED IN THIS DUNGEON CRAWLER. FINISH ALL THE GAMES TO ESCAPE WITHOUT LOSING YOUR HEALTH TO ESCAPE" << endl;
    cout << "YOU ARE P, AT THE START OF THE DUNGEON.\nT = TRAP, HEALTH WILL BE DEDUCTED BY 20 IF LANDED ON IT\nH = HEALTH POTIONS, HEALTH WILL INCREASE BY 10 IF LANDED ON IT\nG = GAME, THIS WILL BE A MINIGAME OF SORT THAT YOU HAVE TO FINISH, IF LOST, HEALTH WILL BE DEDUCTED BY 40\n";
    cout << "PRESS " << Up << " TO MOVE UPWARDS BY 1 POSITION" << endl;
    cout << "PRESS " << Left << " TO MOVE LEFT BY 1 POSITION" << endl;
    cout << "PRESS " << Down << " TO MOVE DOWNWARDS BY 1 POSITION" << endl;
    cout << "PRESS " << Right << " TO MOVE RIGHT BY 1 POSITION" << endl;
    cout << "FOR EXAMPLE, IF YOU WANT TO MOVE 3 PLACES RIGHT AND 3 PLACES DOWN, PRESS DDDSSS AND THEN CLICK ENTER\n";
    char maze[Dimension * Dimension];
    makeMaze(maze);
    maze[0] = 'P';
    int pos = 0, health = 100, counter = 0;
    cout << "\nHEALTH : " << health << endl;
    printMaze(maze);
    bool gameOver = false;
    while (!gameOver)
    {
        string move;
        cout << "\nENTER YOUR MOVE: ";
        cin >> move;
        while (!movePlayer(maze, move, pos, health, games, counter))
        {
            cout << "YOU WENT OUT OF THE DUNGEON. ENTER YOUR MOVE AGAIN: ";
            cin >> move;
        }
        cout << "\nHEALTH : "
             << health << endl;
        printMaze(maze);
        if (health <= 0)
        {
            gameOver = true;
            cout << "\n YOU LOST!";
        }
        else if (counter == 5)
        {
            gameOver = true;
            cout << "\nYOU HAVE SUCCESFULLY FINISHED EACH GAME WITHOUT DYING, YOU ARE OUT OF THE DUNGEON!";
        }
    }
}