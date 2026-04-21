#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <bits/stdc++.h>

using namespace std;

class Board{
private:
    Piece* Grid[8][8];

public:
    Board();

    void Initialize();
    void Print_Board(bool White);
    void Move_Piece(pair<int,int> Source, pair<int, int> Destination);
    bool Is_Valid_Move(pair<int,int> Source, pair<int, int> Destination);
};

#endif