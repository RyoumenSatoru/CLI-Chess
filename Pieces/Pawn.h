#ifndef PAWN_H
#define PAWN_H

#include "../Piece.h"

class Pawn : public Piece{
public:
    Pawn(char Colour, std::pair<int, int> Starting_Position) : Piece(Colour, Starting_Position) {}

    char Get_Symbol() override{
        return 'P';
    }

    bool Is_Valid_Move(std::pair<int, int> Destination, Piece* Board[8][8]) override{
        return true;
    }
};

#endif