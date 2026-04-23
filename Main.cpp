#include "Board.h"

Board Grid;

std::pair<int, int> Convert_Input(std::string Position){
    int Col = toupper(Position[0]) - 'A';
    int Row = Position[1] - '1';

    return {Row, Col};
}

int main(){
    Grid.Initialize();

    char Current_Player = 'B';
    while(true){
        if(Current_Player == 'B') Current_Player = 'W';
        else Current_Player = 'B';

        Grid.Print_Board(Current_Player);

        if(Current_Player == 'W') std::cout << "White's Move: ";
        else std::cout << "Black's Move: ";

        std::string Pos_1, Pos_2;
        std::cin >> Pos_1 ;

        if(Pos_1 == "0-0"){
            bool Success = Grid.Castling(true, Current_Player);

            if(Success == false){
                std::cout << "Invalid Move" << std::endl;
                Current_Player = (Current_Player == 'W') ? 'B' : 'W';
            }
            continue;
        }
        if(Pos_1 == "0-0-0"){
            bool Success = Grid.Castling(false, Current_Player);

            if(Success == false){
                std::cout << "Invalid Move" << std::endl;
                Current_Player = (Current_Player == 'W') ? 'B' : 'W';
            }
            continue;
        } 

        std::cin >> Pos_2;

        std::pair<int, int> Source = Convert_Input(Pos_1);
        std::pair<int, int> Destination = Convert_Input(Pos_2);

        if(Destination == Grid.Get_EP_Square() && Grid.Get_EP_Available()){
            bool Success = Grid.En_Passant(Source, Current_Player);

            if(Success == false){
                std::cout << "Invalid Move" << std::endl;
                Current_Player = (Current_Player == 'W') ? 'B' : 'W';
            }
            continue;

        }

        bool Success = Grid.Move_Piece(Source, Destination, Current_Player);

        if(Success == false){
            std::cout << "Invalid Move" << std::endl;
            Current_Player = (Current_Player == 'W') ? 'B' : 'W';
        }
    }
}