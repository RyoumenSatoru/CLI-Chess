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
    std::pair<int, int> EP_Square;
    bool EP_Available;
public:
    void Initialize();
    void Print_Board(char Current_Player);
    bool Move_Piece(std::pair<int, int> Source, std::pair<int, int> Destination, char Current_Player);
    bool Castling(bool Kingside, char Current_Player);
    bool En_Passant(std::pair<int, int> Source, char Current_Player);
    std::pair<int , int> Get_EP_Square(){
        return EP_Square;
    };
    bool Get_EP_Available(){
        return EP_Available;
    }
};

#endif