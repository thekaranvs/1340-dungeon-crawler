#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

void printBoard(char b[9])
{
    for (int i = 0; i < 9; i++)
    {
        if ((i + 1) % 3 == 0)
        {
            cout << " " << b[i] << " " << endl
                 << " - - - - - " << endl;
        }
        else
        {
            cout << " " << b[i] << " "
                 << "|";
        }
    }
}

bool legitMove(char b[9], int index)
{
    if (index < 0 || index > 8)
        return false;
    else if (b[index] == 'X' || b[index] == 'O')
        return false;
    return true;
}

void placeMove(char b[9], int index, int turn)
{
    if (turn == 1)
        b[index] = 'X';
    else
        b[index] = 'O';
}

int checkColumn(char b[9])
{
    for (int i = 0; i < 3; i++)
    {
        vector<char> check;
        check.push_back(b[i]);
        check.push_back(b[i + 3]);
        check.push_back(b[i + 6]);
        if (count(check.begin(), check.end(), 'X') == 3)
        {
            return -1;
        }
        else if (count(check.begin(), check.end(), 'O') == 3)
            return -1;
        else if (count(check.begin(), check.end(), 'O') == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                if (check[j] != 'X' && check[j] != 'O')
                {
                    return check[j] - '0';
                }
            }
        }
        else if (count(check.begin(), check.end(), 'X') == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                if (check[j] != 'X' && check[j] != 'O')
                {
                    return check[j] - '0';
                }
            }
        }
    }
    return -2;
}

int checkRow(char b[9])
{
    for (int i = 0; i < 9; i += 3)
    {
        vector<char> check;
        check.push_back(b[i]);
        check.push_back(b[i + 1]);
        check.push_back(b[i + 2]);
        if (count(check.begin(), check.end(), 'X') == 3)
            return -1;
        else if (count(check.begin(), check.end(), 'O') == 3)
            return -1;
        else if (count(check.begin(), check.end(), 'O') == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                if (check[j] != 'X' && check[j] != 'O')
                {
                    return check[j] - '0';
                }
            }
        }
        else if (count(check.begin(), check.end(), 'X') == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                if (check[j] != 'X' && check[j] != 'O')
                {
                    return check[j] - '0';
                }
            }
        }
    }
    return -2;
}

int checkDiagonal(char b[9])
{
    for (int i = 0; i < 3; i += 2)
    {
        vector<char> check;
        check.push_back(b[i]);
        check.push_back(b[4]);
        if (i == 0)
            check.push_back(b[i + 8]);
        else
            check.push_back(b[i + 4]);
        if (count(check.begin(), check.end(), 'X') == 3)
            return -1;
        else if (count(check.begin(), check.end(), 'O') == 3)
            return -1;
        else if (count(check.begin(), check.end(), 'O') == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                if (check[j] != 'X' && check[j] != 'O')
                {
                    return check[j] - '0';
                }
            }
        }

        else if (count(check.begin(), check.end(), 'X') == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                if (check[j] != 'X' && check[j] != 'O')
                {
                    return check[j] - '0';
                }
            }
        }
    }
    return -2;
}

bool gameOver(char b[9])
{
    if (checkColumn(b) == -1)
        return true;
    else if (checkRow(b) == -1)
        return true;
    else if (checkDiagonal(b) == -1)
        return true;
    else
        return false;
}

int nextMove(char b[9])
{
    if (checkColumn(b) > -1)
    {
        return checkColumn(b);
    }
    else if (checkRow(b) > -1)
    {
        return checkRow(b);
    }
    else if (checkDiagonal(b) > -1)
    {
        return checkDiagonal(b);
    }
    else
    {
        srand(time(NULL));
        int randomIndex = rand() % 9;
        while (!legitMove(b, randomIndex))
        {
            randomIndex = rand() % 9;
        }
        return randomIndex;
    }
}
