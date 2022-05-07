#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

struct User // a user strucutre which stores the users player string, its position on the board, and its previous position
{
    string player;
    int position = 0;
    string prevPosition = "00";
};

// this function serves to make random ladders in the board
// it has an input of the vector which stores the positions of the ladder
// outputs nothing since void function
void makeLadders(vector<int> &ladders)
{
    srand(time(NULL));
    for (int i = 0; i < 8; i++)
    {
        int random = (rand() % 84) + 1;
        while (count(ladders.begin(), ladders.end(), random) != 0)
        {
            random = (rand() % 84) + 1;
        }
        ladders.push_back(random);
    }
}

// this function serves to make random snakes in the board
// has an input of both the vector which stores the positions of ladders and snakes
// outputs nothing since void function
void makeSnakes(vector<int> &ladders, vector<int> &snakes)
{
    srand(time(NULL));
    for (int i = 0; i < 8; i++)
    {
        int random = (rand() % 84) + 15;
        while (count(ladders.begin(), ladders.end(), random) != 0 && count(snakes.begin(), snakes.end(), random) != 0)
        {
            random = (rand() % 84) + 15;
        }
        snakes.push_back(random);
    }
}

// makes the board array
// has an input of the board array
// no output since void function
void makeBoard(string b[100])
{
    vector<int> ladders;
    vector<int> snakes;
    makeLadders(ladders);
    makeSnakes(ladders, snakes);
    for (int i = 0; i < 100; i++)
    {
        if (count(ladders.begin(), ladders.end(), i) == 1)
        {
            b[i] = "LA";
        }
        else if (count(snakes.begin(), snakes.end(), i) == 1)
        {
            b[i] = "SN";
        }
        else if (i < 10)
        {
            b[i] = "0" + to_string(i);
        }
        else
        {
            b[i] = to_string(i);
        }
    }
}

// prints the board
// has an input of the board array
// no output as void function
void printBoard(string board[100])
{
    cout << endl;
    for (int i = 99; i > -1; i--)
    {
        if (i % 10 == 0)
        {
            cout << board[i] << endl;
        }
        else
        {
            cout << board[i] << " ";
        }
    }
}

// this is when a player lands on snakes or ladders, and is a helper function for the next function which makes moves in the board
// has an input of the board array, the position of the player, the previous position of the player and the player symbol string
// no output as void function
void snakeOrLadder(string board[100], int &pos, string &prev, string player)
{
    int step;
    if (board[pos] == "LA")
    {
        srand(time(NULL));
        step = 1 + (rand() % 15);
        cout << endl
             << player << " landed on a ladder! The ladder is of length " << step;
        board[pos] = prev;
        pos += step;
        prev = board[pos];
    }
    else if (board[pos] == "SN")
    {
        srand(time(NULL));
        step = -(1 + (rand() % 15));
        cout << endl
             << player << " landed on a snake! The snake is of length " << step;
        board[pos] = prev;
        pos += step;
        prev = board[pos];
    }
}

// this makes the move in the board according to the roll of the player
// has an input of the board array, the position of the player, the previous position of the player and the player symbol string
// no output as void function
void makeMove(string board[100], int &pos, string &prev, int move, string player)
{
    board[pos - move] = prev;
    prev = board[pos];
    while (prev == "SN" || prev == "LA")
    {
        snakeOrLadder(board, pos, prev, player);
    }
    board[pos] = player;
}

// this function is for the player to roll the dice, and it also takes care of the error handling
// has an input of the board array, the position of the player, the previous position of the player and the player symbol string
// no output as void function
void playerMove(string board[100], int &pos, string &prev, string player)
{
    char roll;
    int move;
    cout
        << "Press R to roll the dice from 1 to 12.";
    cin >> roll;
    while (roll != 'R')
    {
        cout
            << "\nInvalid Move. Press R to roll the dice from 1 to 12.";
        cin >> roll;
    }
    srand(rand());
    move = (rand() % 12) + 1;
    cout << endl
         << "You rolled a " << move;
    pos += move;
    while (pos > 99)
    {
        pos -= move;
        cout << "\nYou rolled over 99, roll again.";
        cout << "\nPress R to roll the dice from 1 to 12.";
        cin >> roll;
        while (roll != 'R')
        {
            cout << "\nInvalid Move. Press R to roll the dice from 1 to 12.";
            cin >> roll;
        }
        srand(time(NULL));
        move = (rand() % 12) + 1;
        cout << "\nYou rolled a " << move;
        pos += move;
    }
    makeMove(board, pos, prev, move, player);
}
