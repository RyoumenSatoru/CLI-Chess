#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Pieces/Pawn.h"
#include "Pieces/Rook.h"
#include "Pieces/Bishop.h"
#include "Pieces/Knight.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"

class Board{
private:
    Piece* Chess_Board[8][8];
public:
    void Initialize();
    void Print_Board(char Current_Player);
    bool Move_Piece(std::pair<int, int> Source, std::pair<int, int> Destination, char Current_Player);
};

#endif