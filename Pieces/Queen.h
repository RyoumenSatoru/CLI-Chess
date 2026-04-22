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
        int Src_Row = Current_Position.first;
        int Src_Col = Current_Position.second;

        int Dest_Row = Destination.first;
        int Dest_Col = Destination.second;

        if((Dest_Row != Src_Row && Dest_Col != Src_Col) && (abs(Src_Row - Dest_Row) != abs(Src_Col - Dest_Col))){
            return false;
        } 

        if(Dest_Row == Src_Row){
            int Start = std::min(Src_Col, Dest_Col);
            int End = std::max(Dest_Col, Src_Col);

            for(int j = Start + 1; j < End; j++){
                if(Board[Src_Row][j] != nullptr){
                    return false;
                }
            }
        }

        if(Dest_Col == Src_Col){
            int Start = std::min(Dest_Row, Src_Row);
            int End = std::max(Dest_Row, Src_Row);

            for(int i = Start + 1; i < End; i++){
                if(Board[i][Src_Col] != nullptr){
                    return false;
                }
            }
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