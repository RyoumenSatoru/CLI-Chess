#ifndef QUEEN_H
#define QUEEN_H

#include "../Piece.h"

class Queen : public Piece{
public:
    Queen(char Colour, std::pair<int, int> Starting_Position) : Piece(Colour, Starting_Position) {}

    char Get_Symbol() override{
        return 'Q';
    }
};

#endif