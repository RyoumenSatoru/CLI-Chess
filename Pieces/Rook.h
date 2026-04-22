#ifndef ROOK_H
#define ROOK_H

#include "../Piece.h"

class Rook : public Piece{
public:
    Rook(char Colour, std::pair<int, int> Starting_Position) : Piece(Colour, Starting_Position) {}

    char Get_Symbol() override{
        return 'R';
    }

    bool Is_Valid_Move(std::pair<int, int> Destination, Piece* Board[8][8]) override{
        int Src_Row = Current_Position.first;
        int Src_Col = Current_Position.second;
        
        int Dest_Row = Destination.first;
        int Dest_Col = Destination.second;

        if(Dest_Row != Src_Row && Dest_Col != Src_Col){
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

        return true;
    }
};

#endif