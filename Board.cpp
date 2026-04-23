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

    EP_Available = false;
    EP_Square = {-1, -1};
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
    Chess_Board[Destination.first][Destination.second]->Set_Has_Moved();

    EP_Available = false;

    if(Chess_Board[Destination.first][Destination.second]->Get_Symbol() == 'P' && abs(Source.first - Destination.first) == 2){
        EP_Available = true;

        EP_Square = (Current_Player == 'W') ? std::make_pair(Destination.first - 1, Destination.second) : std::make_pair(Destination.first + 1, Destination.second);
    }

    int End_Row = (Current_Player == 'W') ? 7 : 0;

    if(Chess_Board[Destination.first][Destination.second]->Get_Symbol() == 'P' && Destination.first == End_Row){
        char Promoted_Piece;
        std::cout << "Promote To (Q R B N): ";
        std::cin >> Promoted_Piece;

        delete Chess_Board[Destination.first][Destination.second];

        if(Promoted_Piece == 'R') Chess_Board[Destination.first][Destination.second] = new Rook(Current_Player, Destination);
        else if(Promoted_Piece == 'N') Chess_Board[Destination.first][Destination.second] = new Knight(Current_Player, Destination);
        else if(Promoted_Piece == 'B') Chess_Board[Destination.first][Destination.second] = new Bishop(Current_Player, Destination);
        else{
            Chess_Board[Destination.first][Destination.second] = new Queen(Current_Player, Destination);
        }
    }

    
    return true;
}

bool Board::Castling(bool Kingside, char Current_Player){
    int Row = (Current_Player == 'W') ? 0 : 7;
    int Rook_Col = (Kingside == true) ? 7 : 0;

    int Start_Col = std::min(4, Rook_Col);
    int End_Col = std::max(4, Rook_Col);

    if(Chess_Board[Row][4] == nullptr || Chess_Board[Row][4]->Get_Has_Moved()){
        return false;
    }
    if(Chess_Board[Row][Rook_Col] == nullptr || Chess_Board[Row][Rook_Col]->Get_Has_Moved()){
        return false;
    }

    for(int i = Start_Col + 1; i < End_Col; i++){
        if(Chess_Board[Row][i] != nullptr){
            return false;
        }
    }
    

    int King_End_Col = (Kingside == true) ? 6 : 2;
    int Rook_End_Col = (Kingside == true) ? 5 : 3;

    delete Chess_Board[Row][King_End_Col];
    delete Chess_Board[Row][Rook_End_Col];

    Chess_Board[Row][King_End_Col] = Chess_Board[Row][4];
    Chess_Board[Row][Rook_End_Col] = Chess_Board[Row][Rook_Col];

    Chess_Board[Row][4] = nullptr;
    Chess_Board[Row][Rook_Col] = nullptr;

    Chess_Board[Row][King_End_Col]->Set_Has_Moved();
    Chess_Board[Row][King_End_Col]->Set_Position({Row, King_End_Col});

    Chess_Board[Row][Rook_End_Col]->Set_Has_Moved();
    Chess_Board[Row][Rook_End_Col]->Set_Position({Row, Rook_End_Col});

    return true;
}

bool Board::En_Passant(std::pair<int ,int> Source, char Current_Player){
    if(EP_Available == false){
        return false;
    }

    if(Chess_Board[Source.first][Source.second] == nullptr || Chess_Board[Source.first][Source.second]->Get_Color() != Current_Player){
        return false;
    }

    if(Chess_Board[EP_Square.first][EP_Square.second] != nullptr){
        return false;
    }

    int Direction = (Current_Player == 'W') ? -1 : 1;

    if(abs(Source.second - EP_Square.second) != 1 || Source.first != EP_Square.first + Direction){
        return false;
    }

    if(Chess_Board[EP_Square.first + Direction][EP_Square.second] == nullptr){
        return false;
    }

    if(Chess_Board[EP_Square.first + Direction][EP_Square.second]->Get_Color() == Current_Player){
        return false;
    }

    delete Chess_Board[EP_Square.first][EP_Square.second];
    Chess_Board[EP_Square.first][EP_Square.second] = Chess_Board[Source.first][Source.second];
    Chess_Board[Source.first][Source.second] = nullptr;
    Chess_Board[EP_Square.first][EP_Square.second]->Set_Position(EP_Square);

    delete Chess_Board[EP_Square.first + Direction][EP_Square.second];
    Chess_Board[EP_Square.first + Direction][EP_Square.second] = nullptr;

    EP_Available = false;
    EP_Square = {-1, -1};
    return true;

}