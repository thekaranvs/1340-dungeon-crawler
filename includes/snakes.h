#ifndef SNAKES_H
#define SNAKES_H

#include <iostream>
#include <string>
#include <vector>

struct User
{
    std::string player;
    int position = 0;
    std::string prevPosition = "00";
};

void makeLadders(std::vector<int> &);

void makeSnakes(std::vector<int> &, std::vector<int> &);

void makeBoard(std::string *);

void printBoard(std::string *);

void snakeOrLadder(std::string *, int &, std::string &, std::string);

void makeMove(std::string *, int &, std::string &, int, std::string);

void playerMove(std::string *, int &, std::string &, std::string);

#endif
