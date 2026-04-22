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

        int Start_Row = (Dest_Row > Src_Row) ? Src_Row : Dest_Row;
        int End_Row = (Dest_Row > Src_Row) ? Dest_Row : Src_Row;
        
        int Start_Col = (Dest_Col > Src_Col) ? Src_Col : Dest_Col;
        int End_Col = (Dest_Col > Src_Col) ? Dest_Col : Src_Col;

        for(int i = Start_Row + 1, j = Start_Col + 1; i < End_Row && j < End_Col; i++, j++){
            if(Board[i][j] != nullptr){
                return false;
            }
        }

        return true;
    }
};

#endif