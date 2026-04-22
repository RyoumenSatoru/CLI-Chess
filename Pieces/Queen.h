#ifndef QUEEN_H
#define QUEEN_H

#include "../Piece.h"

class Queen : public Piece{
public:
    Queen(char Colour, std::pair<int, int> Starting_Position) : Piece(Colour, Starting_Position) {}

    char Get_Symbol() override{
        return 'Q';
    }

    bool Is_Valid_Move(std::pair<int, int> Destination, Piece* Board[8][8]) override{
        return true;
    }
};

#endif