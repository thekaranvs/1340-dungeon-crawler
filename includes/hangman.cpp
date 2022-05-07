#include <iostream>
#include <string>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;

// this function gets a random word from the words array
// has an input of the array of possible words, and the length of the word chosen
// returns the word chosen
string getRandomWord(string w[10], int &length)
{
    srand(time(NULL));
    int index = rand() % 10;
    length = w[index].size();
    return w[index];
}

// this function prints the hangman
// has an input of the variable guesses, which sotres the amount of wrong guesses made
// no output since a void function
void printMan(int guesses)
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
// this function serves to get the guesses of alphabets from the users and then comprehend it, and also returns true when out of guesses
// has an input of a pointer to a characther, the number of wrong guesses, the length of the chosen word and the vector b which keeps track of all the alphabets already guessed
// has an output of true if word is guessed, or else false
bool getGuesses(char *a, int &guesses, int length, vector<char> &b)
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

// this function serves to deal with when the game is over
// has an input of a boolean which stores whether word was guessed or not, and the word which was needed to be guessed
// no output since void function
void endGame(bool r, string word)
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
