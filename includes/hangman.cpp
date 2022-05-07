#include <iostream>
#include <string>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;

string getRandomWord(string w[10], int &length) // this function gets a random word from the words array
{
    srand(time(NULL));
    int index = rand() % 10;
    length = w[index].size();
    return w[index];
}

void printMan(int guesses) // this function prints the hangman
{
    switch (guesses)
    {
    case 1:
        cout << "-----" << endl
             << "|   |" << endl
             << "-----" << endl;
        break;
    case 2:
        cout << "-----" << endl
             << "|   |" << endl
             << "-----" << endl
             << "  |  " << endl
             << "  |  " << endl
             << "  |  " << endl;
        break;
    case 3:
        cout << "-----" << endl
             << "|   |" << endl
             << "-----" << endl
             << "  |  " << endl
             << "  |  " << endl
             << "  |  " << endl
             << " /   " << endl
             << "/    " << endl;
        break;
    case 4:
        cout << "-----" << endl
             << "|   |" << endl
             << "-----" << endl
             << "  |  " << endl
             << "  |  " << endl
             << "  |  " << endl
             << " / \\" << endl
             << "/   \\" << endl;
        break;
    case 5:
        cout << "-----" << endl
             << "|   |" << endl
             << "-----" << endl
             << "  |  " << endl
             << "--|  " << endl
             << "  |  " << endl
             << " / \\" << endl
             << "/   \\" << endl;
        break;
    case 6:
        cout << "-----" << endl
             << "|   |" << endl
             << "-----" << endl
             << "  |  " << endl
             << "--|--" << endl
             << "  |  " << endl
             << " / \\ " << endl
             << "/   \\  " << endl;
        break;
    case 7:
        cout << "-----" << endl
             << "|* *|" << endl
             << "-----" << endl
             << "  |  " << endl
             << "--|--" << endl
             << "  |  " << endl
             << " / \\" << endl
             << "/   \\" << endl;
        break;
    }
}

bool getGuesses(char *a, int &guesses, int length, vector<char> &b) // this function serves to get the guesses of alphabets from the users and then comprehend it, and also returns true when out of guesses
{
    string toPrint;
    int guessed = 0;
    for (int i = 0; i < length; i++)
    {
        toPrint += "_";
    }
    while (guesses < 7 && guessed != length)
    {
        cout << "Enter an Alphabet in Lower Caps: ";
        char guess;
        cin >> guess;
        if (count(b.begin(), b.end(), guess) < 2)
        {
            b.push_back(guess);
        }
        bool correct;
        while (count(b.begin(), b.end(), guess) > 1)
        {
            cout << "\nYou already guessed this Alphabet. Please enter a new Alphabet.";
            cout << "\n\nEnter an Alphabet in Lower Caps: ";
            cin >> guess;
            if (count(b.begin(), b.end(), guess) < 2)
            {
                b.push_back(guess);
            }
        }
        for (int i = 0; i < length; i++)
        {
            if (a[i] == guess)
            {
                correct = true;
                guessed++;
                toPrint[i] = a[i];
            }
        }
        cout << toPrint << endl;
        if (!correct)
        {
            guesses++;
            cout << endl;
            printMan(guesses);
            cout << endl;
        }
        correct = false;
    }
    return (guessed == length);
}

void endGame(bool r, string word) // this function serves to deal with when the game is over
{
    transform(word.begin(), word.end(), word.begin(), ::toupper);
    cout << endl;
    if (r)
    {
        cout << "Congrats! You guessed the word " << word << " Correctly.";
    }
    else
    {
        cout << "You are out of guesses! You lost, 40 point is deducted from your health.";
    }
}
