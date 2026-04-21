#include "Board.h"

Board::Board(){
    Initialize();
}

void Board::Initialize(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Grid[i][j] = nullptr;
        }
    }

    //Pawns
    for(int j = 0; j < 8; j++){
        Grid[1][j] = new Piece('P', 'B');
        Grid[6][j] = new Piece('P', 'W');
    }

    //Rooks
    Grid[0][0] = Grid[0][7] = new Piece('R', 'B');
    Grid[7][0] = Grid[7][7] = new Piece('R', 'W');

    //Knights
    Grid[0][1] = Grid[0][6] = new Piece('N', 'B');
    Grid[7][1] = Grid[7][6] = new Piece('N', 'W');

    //Bishops
    Grid[0][2] = Grid[0][5] = new Piece('B', 'B');
    Grid[7][2] = Grid[7][5] = new Piece('B', 'W');

    //Queens
    Grid[0][3] = new Piece('Q', 'B');
    Grid[7][3] = new Piece('Q', 'W');
    
    //Kings
    Grid[0][4] = new Piece('K', 'B');
    Grid[7][4] = new Piece('K', 'W');
}

void Board::Print_Board(bool White){
    for(int i = 0; i < 8; i++){
        int Row = i;
        if(!White) Row = 7 - i;

        if(White){
            cout << 8 - i << "  ";
        }
        else{
            cout << i + 1 << "  ";
        }

        for(int j = 0; j < 8; j++){
            int Col = j;
            if(!White) Col = 7 - j;
            
            if(Grid[Row][Col] == nullptr){
                cout << "." << " ";
            }
            else{
                if(Grid[Row][Col]->Colour == 'W'){
                    cout << "\033[32m" << Grid[Row][Col]->Symbol << "\033[0m ";
                }
                else if(Grid[Row][Col]->Colour == 'B'){
                    cout << "\033[31m" << Grid[Row][Col]->Symbol << "\033[0m ";
                }
            }
        }
        cout << endl;
    }
    if(White){
        cout << "   A B C D E F G H" << "\n\n";
    }
    else{
        cout << "   H G F E D C B A" << "\n\n";
    }
}

void Board::Move_Piece(pair<int, int> Source, pair<int, int> Destination){
    if(!Is_Valid_Move(Source, Destination)){
        cout << "Invalid Move!" << endl;
        return;
    }
    Piece* Temp = Grid[Source.first][Source.second];
    Grid[Source.first][Source.second] = nullptr;
    Grid[Destination.first][Destination.second] = Temp;
}

bool Board::Is_Valid_Move(pair<int,int> Source, pair<int, int> Destination){
    int Src_Row = Source.first;
    int Src_Col = Source.second;
    int Dest_Row = Destination.first;
    int Dest_Col = Destination.second;

    Piece *Source_Piece = Grid[Src_Row][Src_Col];
    Piece *Dest_Piece = Grid[Dest_Row][Dest_Col];

    if(Source_Piece == nullptr) return false;

    if(Source_Piece->Symbol == 'P'){
        if(Source_Piece->Colour == 'B'){
            //Move by 2
            if(Dest_Row == Src_Row + 2){
                if(Src_Row == 1 && 
                   Dest_Col == Src_Col &&
                   Grid[Src_Row + 1][Src_Col] == nullptr && 
                   Dest_Piece == nullptr) 
                   return true;
            }

            //Move by 1
            if(Dest_Row == Src_Row + 1 && 
               Dest_Col == Src_Col && 
               Dest_Piece == nullptr) 
               return true;

            //Capture
            if(Dest_Row == Src_Row + 1 && 
               abs(Dest_Col - Src_Col) == 1 && 
               Dest_Piece != nullptr && 
               Dest_Piece->Colour == 'W') 
               return true;
        }
        
        else{
            //Move by 2
            if(Dest_Row == Src_Row - 2){
                if(Src_Row == 6 && 
                   Dest_Col == Src_Col &&
                   Grid[Src_Row - 1][Src_Col] == nullptr && 
                   Dest_Piece == nullptr) 
                   return true;
            }

            //Move by 1
            if(Dest_Row == Src_Row - 1 && 
               Dest_Col == Src_Col && 
               Dest_Piece == nullptr) 
               return true;

            //Capture
            if(Dest_Row == Src_Row - 1 && 
               abs(Dest_Col - Src_Col) == 1 && 
               Dest_Piece != nullptr && 
               Dest_Piece->Colour == 'B') 
               return true;
        }
    }
    
    return false;
}