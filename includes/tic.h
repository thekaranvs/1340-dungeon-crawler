#ifndef TIC_H
#define TIC_H

#include <vector>
#include <iostream>

void printBoard(char *);

bool legitMove(char *, int);

void placeMove(char *, int, int);

int checkColumn(char *);

int checkRow(char *);

int checkDiagonal(char *);

bool gameOver(char *);

int nextMove(char *);

#endif
