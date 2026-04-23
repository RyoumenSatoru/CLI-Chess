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
        int Src_Row = Current_Position.first;
        int Src_Col = Current_Position.second;

        int Dest_Row = Destination.first;
        int Dest_Col = Destination.second;

        int Row_Diff = abs(Dest_Row - Src_Row);
        int Col_Diff = abs(Dest_Col - Src_Col);

        if(Row_Diff == 0 && Col_Diff == 0){
            return false;
        }

        if(Row_Diff <= 1 && Col_Diff <= 1){
            return true;
        }
        
        return false;
    }
};

#endif