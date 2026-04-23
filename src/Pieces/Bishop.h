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
        int Src_Row = Current_Position.first;
        int Src_Col = Current_Position.second;

        int Dest_Row = Destination.first;
        int Dest_Col = Destination.second;

        if(abs(Src_Row - Dest_Row) != abs(Src_Col - Dest_Col)){
            return false;
        }

        int row_dir = (Dest_Row > Src_Row) ? 1 : -1;
        int col_dir = (Dest_Col > Src_Col) ? 1 : -1;

        int r = Src_Row + row_dir;
        int c = Src_Col + col_dir;

        while(r != Dest_Row && c != Dest_Col){
            if(Board[r][c] != nullptr) return false;
            r += row_dir;
            c += col_dir;
        }

        return true;
    }
};

#endif