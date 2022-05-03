#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

struct User
{
    string player;
    int position = 0;
    string prevPosition = "00";
};

void makeLadders(vector<int> &ladders)
{
    srand(time(NULL));
    for (int i = 0; i < 8; i++)
    {
        int random = (rand() % 99) + 1;
        while (count(ladders.begin(), ladders.end(), random) != 0 && random != 0)
        {
            random = (rand() % 99) + 1;
        }
        ladders.push_back(random);
    }
}

void makeSnakes(vector<int> &ladders, vector<int> &snakes)
{
    srand(time(NULL));
    for (int i = 0; i < 8; i++)
    {
        int random = (rand() % 99) + 1;
        while (count(ladders.begin(), ladders.end(), random) != 0 && count(snakes.begin(), snakes.end(), random) != 0 && random != 0)
        {
            random = (rand() % 99) + 1;
        }
        snakes.push_back(random);
    }
}

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
