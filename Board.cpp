#include "Board.h"

void Board::Initialize(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Chess_Board[i][j] = nullptr;
        }
    }

    //Pawns
    for(int j = 0; j < 8; j++){
        Chess_Board[1][j] = new Pawn('W', {1, j});
        Chess_Board[6][j] = new Pawn('B', {6, j});
    }

    //Rooks
    Chess_Board[0][0] = new Rook('W', {0, 0});
    Chess_Board[0][7] = new Rook('W', {0, 7});

    Chess_Board[7][0] = new Rook('B', {7, 0});
    Chess_Board[7][7] = new Rook('B', {7, 7});

    //Knights
    Chess_Board[0][1] = new Knight('W', {0, 1});
    Chess_Board[0][6] = new Knight('W', {0, 6});

    Chess_Board[7][1] = new Knight('B', {7, 1});
    Chess_Board[7][6] = new Knight('B', {7, 6});

    //Bishops
    Chess_Board[0][2] = new Bishop('W', {0, 2});
    Chess_Board[0][5] = new Bishop('W', {0, 5});

    Chess_Board[7][2] = new Bishop('B', {7, 2});
    Chess_Board[7][5] = new Bishop('B', {7, 5});

    //Kings
    Chess_Board[0][4] = new King('W', {0, 4});
    Chess_Board[7][4] = new King('B', {7, 4});

    //Queens
    Chess_Board[0][3] = new Queen('W', {0, 3});
    Chess_Board[7][3] = new Queen('B', {7, 3});
}

void Board::Print_Board(char Current_Player){
    for(int i = 0; i < 8; i++){
        int Row = 7 - i;
        if(Current_Player == 'B') Row = i;

        std::cout << Row + 1 << " ";

        for(int j = 0; j < 8; j++){
            int Col = j;
            if(Current_Player == 'B') Col = 7 - j;

            if(Chess_Board[Row][Col] == nullptr){
                std::cout << "." << " ";
            }
            else{
                Chess_Board[Row][Col]->Display_Symbol();
            }
            
        }
        std::cout << std::endl; 
    }

    if(Current_Player == 'W') std::cout << "  A B C D E F G H" << std::endl; 
    else std::cout << "  H G F E D C B A" << std::endl;
}

bool Board::Move_Piece(std::pair<int, int> Source, std::pair<int, int> Destination, char Current_Player){
    if(Chess_Board[Source.first][Source.second] == nullptr){
        return false;
    }

    if(Chess_Board[Source.first][Source.second]->Get_Color() != Current_Player){
        return false;
    }

    if(Chess_Board[Source.first][Source.second]->Is_Valid_Move(Destination, Chess_Board) == false){
        return false;
    }

    if(Chess_Board[Destination.first][Destination.second] != nullptr && Chess_Board[Destination.first][Destination.second]->Get_Color() == Current_Player){
        return false;
    }

    delete Chess_Board[Destination.first][Destination.second];
    Chess_Board[Destination.first][Destination.second] = Chess_Board[Source.first][Source.second];
    Chess_Board[Source.first][Source.second] = nullptr;
    Chess_Board[Destination.first][Destination.second]->Set_Position(Destination);
    return true;
}