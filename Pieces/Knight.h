#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Piece.h"

class Knight : public Piece{
public:
    Knight(char Colour, std::pair<int, int> Starting_Position) : Piece(Colour, Starting_Position) {}

    char Get_Symbol() override{
        return 'N';
    }

    bool Is_Valid_Move(std::pair<int, int> Destination, Piece* Board[8][8]) override{
        return true;
    }
};

#endif