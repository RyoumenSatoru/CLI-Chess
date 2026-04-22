#ifndef BISHOP_H
#define BISHOP_H

#include "../Piece.h"

class Bishop : public Piece{
public:
    Bishop(char Colour, std::pair<int, int> Starting_Position) : Piece(Colour, Starting_Position) {}

    char Get_Symbol() override{
        return 'B';
    }

    bool Is_Valid_Move(std::pair<int, int> Destination, Piece* Board[8][8]) override{
        return true;
    }
};

#endif