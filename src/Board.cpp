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
    White_King = {0, 4};
    Black_King = {7, 4};
}

void Board::Print_Board(bool White_Move){
    if(White_Move) std::cout << "    A   B   C   D   E   F   G   H" << std::endl; 
    else std::cout << "    H   G   F   E   D   C   B   A" << std::endl;

    for(int i = 0; i < 8; i++){
        int Row = 7 - i;
        if(!White_Move) Row = i;

        if(i == 0){
            std::cout << "  ┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓\n";
        }
        else{
            std::cout << "  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫\n";
        }

        std::cout << Row + 1 << " ";

        for(int j = 0; j < 8; j++){
            int Col = j;
            if(!White_Move) Col = 7 - j;

            std::cout << "┃";

            if(Chess_Board[Row][Col] == nullptr){
                std::cout << "   ";
            }
            else{
                Chess_Board[Row][Col]->Display_Symbol();
            }

        }
        std::cout << "┃ " << Row + 1 << std::endl;
    }
    std::cout << "  ┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛" << std::endl;

    if(White_Move) std::cout << "    A   B   C   D   E   F   G   H" << std::endl; 
    else std::cout << "    H   G   F   E   D   C   B   A" << std::endl;
}

bool Board::Move_Piece(std::pair<int, int> Source, std::pair<int, int> Destination, char Current_Player){
    std::pair<int, int> King_Position = (Current_Player == 'W') ? White_King : Black_King;

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

    Piece* Temp_Destination  = Chess_Board[Destination.first][Destination.second];

    Chess_Board[Destination.first][Destination.second] = Chess_Board[Source.first][Source.second];
    Chess_Board[Source.first][Source.second] = nullptr;

    EP_Available = false;

    if(Chess_Board[Destination.first][Destination.second]->Get_Symbol() == 'P' && abs(Source.first - Destination.first) == 2){
        EP_Available = true;

        EP_Square = (Current_Player == 'W') ? std::make_pair(Destination.first - 1, Destination.second) : std::make_pair(Destination.first + 1, Destination.second);
    }

    int End_Row = (Current_Player == 'W') ? 7 : 0;

    if(Chess_Board[Destination.first][Destination.second]->Get_Symbol() == 'K') King_Position = Destination;

    if(Is_In_Check(Current_Player, King_Position)){
        Chess_Board[Source.first][Source.second] = Chess_Board[Destination.first][Destination.second];
        Chess_Board[Destination.first][Destination.second] = Temp_Destination;

        std::cout << "Invalid — leaves King in check" << std::endl;
        return false; 
    }

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

    if(Chess_Board[Destination.first][Destination.second]->Get_Symbol() == 'K'){
        if(Chess_Board[Destination.first][Destination.second]->Get_Color() == 'W'){
            White_King = Destination;
        }
        else{
            Black_King = Destination;
        }
    }
    
    Chess_Board[Destination.first][Destination.second]->Set_Position(Destination);
    Chess_Board[Destination.first][Destination.second]->Set_Has_Moved();
    delete Temp_Destination;
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

    for(int i = Start_Col; i <= End_Col; i++){
        if(Is_In_Check(Current_Player, {Row, i})){
            std::cout << "Invalid — leaves King in check" << std::endl;
            return false;
        }
        if(i == Start_Col || i == End_Col) continue;
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
    if(Current_Player == 'W'){
        White_King = {Row, King_End_Col};
    }
    else{
        Black_King = {Row, King_End_Col};
    }

    Chess_Board[Row][Rook_End_Col]->Set_Has_Moved();
    Chess_Board[Row][Rook_End_Col]->Set_Position({Row, Rook_End_Col});

    EP_Available = false;
    EP_Square = {-1, -1};

    return true;
}

bool Board::En_Passant(std::pair<int ,int> Source, char Current_Player){
    std::pair<int, int> King_Position = (Current_Player == 'W') ? White_King : Black_King;
 
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

    Piece* Temp = Chess_Board[EP_Square.first + Direction][EP_Square.second];
    
    Chess_Board[EP_Square.first + Direction][EP_Square.second] = nullptr;

    if(Is_In_Check(Current_Player, King_Position)){
        Chess_Board[Source.first][Source.second] = Chess_Board[EP_Square.first][EP_Square.second];
        Chess_Board[EP_Square.first][EP_Square.second] = nullptr;

        Chess_Board[EP_Square.first + Direction][EP_Square.second] = Temp;

        std::cout << "Invalid — leaves King in check" << std::endl;
        return false;
    }

    Chess_Board[EP_Square.first][EP_Square.second]->Set_Position(EP_Square);
    EP_Available = false;
    EP_Square = {-1, -1};
    delete Temp;
    return true;

}

bool Board::Is_In_Check(char Color, std::pair<int, int> King_Position){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(Chess_Board[i][j] != nullptr && Chess_Board[i][j]->Get_Color() != Color){
                if(Chess_Board[i][j]->Is_Valid_Move(King_Position, Chess_Board)){
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::Is_Checkmate(char Current_Player){
    std::pair<int, int> King_Position = (Current_Player == 'W') ? White_King : Black_King;

    if(!Is_In_Check(Current_Player, King_Position)){
        return false;
    }

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(Chess_Board[i][j] != nullptr && Chess_Board[i][j]->Get_Color() == Current_Player){
                for(int x = 0; x < 8; x++){
                    for(int y = 0; y < 8; y++){
                        Piece* Src = Chess_Board[i][j];
                        Piece* Dest = Chess_Board[x][y];

                        if(Src->Is_Valid_Move({x, y}, Chess_Board)){
                            if(Dest == nullptr || Src->Get_Color() != Dest->Get_Color()){
                                Chess_Board[x][y] = Src;
                                Chess_Board[i][j] = nullptr;

                                std::pair<int ,int> New_King = King_Position;
                                if(Src->Get_Symbol() == 'K') New_King = {x, y};

                                bool Still_Check = Is_In_Check(Current_Player, New_King);

                                Chess_Board[i][j] = Src;
                                Chess_Board[x][y] = Dest;

                                if(!Still_Check){
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool Board::Is_Stalemate(char Current_Player){
    std::pair<int, int> King_Position = (Current_Player == 'W') ? White_King : Black_King;

    if(Is_In_Check(Current_Player, King_Position)){
        return false;
    }

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(Chess_Board[i][j] != nullptr && Chess_Board[i][j]->Get_Color() == Current_Player){
                for(int x = 0; x < 8; x++){
                    for(int y = 0; y < 8; y++){
                        Piece* Src = Chess_Board[i][j];
                        Piece* Dest = Chess_Board[x][y];

                        if(Src->Is_Valid_Move({x, y}, Chess_Board)){
                            if(Dest == nullptr || Src->Get_Color() != Dest->Get_Color()){
                                Chess_Board[x][y] = Src;
                                Chess_Board[i][j] = nullptr;

                                std::pair<int ,int> New_King = King_Position;
                                if(Src->Get_Symbol() == 'K') New_King = {x, y};

                                bool Still_Check = Is_In_Check(Current_Player, New_King);

                                Chess_Board[i][j] = Src;
                                Chess_Board[x][y] = Dest;

                                if(!Still_Check){
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}