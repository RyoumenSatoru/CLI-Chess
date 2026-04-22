#ifndef ROOK_H
#define ROOK_H

#include "../Piece.h"

class Rook : public Piece{
public:
    Rook(char Colour, std::pair<int, int> Starting_Position) : Piece(Colour, Starting_Position) {}

    char Get_Symbol() override{
        return 'R';
    }
};

#endif