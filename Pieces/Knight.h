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
        int Src_Row = Current_Position.first;
        int Src_Col = Current_Position.second;

        int Dest_Row = Destination.first;
        int Dest_Col = Destination.second;

        int Row_Diff = abs(Src_Row - Dest_Row);
        int Col_Diff = abs(Src_Col - Dest_Col);

        if((Row_Diff == 1 && Col_Diff == 2) || (Row_Diff == 2 && Col_Diff == 1)){
            return true;
        }

        return false;
    }
};

#endif