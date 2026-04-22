#ifndef KING_H
#define KING_H

#include "../Piece.h"

class King : public Piece{
public:
    King(char Colour, std::pair<int, int> Starting_position) : Piece(Colour, Starting_position) {}

    char Get_Symbol() override{
        return 'K';
    }

    bool Is_Valid_Move(std::pair<int, int> Destination, Piece* Board[8][8]) override{
        return true;
    }
};

#endif