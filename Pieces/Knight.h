#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Piece.h"

class Knight : public Piece{
public:
    Knight(char Colour, std::pair<int, int> Starting_Position) : Piece(Colour, Starting_Position) {}

    char Get_Symbol() override{
        return 'N';
    }
};

#endif