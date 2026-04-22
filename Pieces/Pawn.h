#ifndef PAWN_H
#define PAWN_H

#include "../Piece.h"

class Pawn : public Piece{
public:
    Pawn(char Colour, std::pair<int, int> Starting_Position) : Piece(Colour, Starting_Position) {}

    char Get_Symbol() override{
        return 'P';
    }

    bool Is_Valid_Move(std::pair<int, int> Destination, Piece* Board[8][8]) override{
        int C = Get_Color();
        int Direction = (C == 'W') ? 1 : -1;

        int Src_Row = Current_Position.first;
        int Src_Col = Current_Position.second;

        int Dest_Row = Destination.first;
        int Dest_Col = Destination.second;

        if((Dest_Row == Src_Row + Direction) && (Dest_Col == Src_Col)){
            if(Board[Dest_Row][Dest_Col] != nullptr){
                return false;
            }
            return true;
        }

        if(Dest_Row == Src_Row + (2*Direction) && (Dest_Col == Src_Col)){
            if(Board[Src_Row + Direction][Src_Col] != nullptr || Board[Dest_Row][Dest_Col] != nullptr){
                return false;
            }

            if((Src_Row == 1 && Get_Color() == 'W') || (Src_Row == 6 && Get_Color() == 'B')){
                return true;
            }
        }

        if((Dest_Row == Src_Row + Direction) && (abs(Dest_Col - Src_Col) == 1)){
            if(Board[Dest_Row][Dest_Col] == nullptr){
                return false;
            }

            if(Board[Dest_Row][Dest_Col]->Get_Color() == Board[Src_Row][Src_Col]->Get_Color()){
                return false;
            }

            if(Board[Dest_Row][Dest_Col]->Get_Color() != Board[Src_Row][Src_Col]->Get_Color()){
                return true;
            }
        }

        return false;
    }
};

#endif