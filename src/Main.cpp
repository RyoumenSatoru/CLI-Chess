#include "Board.h"
#include <cstdlib>

Board Grid;

std::pair<int, int> Convert_Input(std::string Position){
    if(Position.length() < 2){
        std::cout << "Inavlid input format" << std::endl;
        return {-1, -1};
    }

    char File = toupper(Position[0]);
    char Rank = Position[1];

    if(File < 'A' || File > 'H'){
        std::cout << "Invalid file character. Use A-H." << std::endl;
        return {-1, -1};
    }

    if(Rank < '1' || Rank > '8'){
        std::cout << "Invalid Rank . Use 1-8." << std::endl;
        return {-1, -1};
    }

    int Col = File - 'A';
    int Row = Rank - '1'; 

    return {Row, Col};
}

int main(){
    Grid.Initialize();

    char Current_Player = 'W';
    while(true){
        //system("clear");

        Grid.Print_Board(Current_Player == 'W');
        if(Grid.Is_In_Check(Current_Player, Grid.Get_King_Position(Current_Player))){
            if(Current_Player == 'B'){
                std::cout << "\033[32m" << "Check!" << "\033[0m" << std::endl;
            }
            else{
                std::cout << "\033[31m" << "Check!" << "\033[0m" << std::endl;
            }
        }

        if(Current_Player == 'W') std::cout << "White's Move: ";
        else std::cout << "Black's Move: ";

        std::string Pos_1, Pos_2;
        std::cin >> Pos_1 ;

        if(Pos_1 == "0-0"){
            bool Success = Grid.Castling(true, Current_Player);

            if(Success){
                if(Grid.Is_Checkmate((Current_Player == 'W') ? 'B' : 'W')){
                    if(Current_Player == 'B'){
                        std::cout << "\033[32m" << "WHITE WINS!" << "\033[0m" << std::endl;
                    }
                    else{
                        std::cout << "\033[31m" << "BLACK WINS" << "\033[0m" << std::endl;
                    }
                    break;
                }

                if(Grid.Is_Stalemate((Current_Player == 'W') ? 'B' : 'W')){
                    std::cout << "Stalemate — Draw!" << std::endl;
                    break;
                }

                Current_Player = (Current_Player == 'W') ? 'B' : 'W';
            }
            else{
                std::cout << "Inavlid Move" << std::endl;
            }
            continue;
        }
        if(Pos_1 == "0-0-0"){
            bool Success = Grid.Castling(false, Current_Player);

            if(Success){
                if(Grid.Is_Checkmate((Current_Player == 'W') ? 'B' : 'W')){
                    if(Current_Player == 'B'){
                        std::cout << "\033[32m" << "WHITE WINS!" << "\033[0m" << std::endl;
                    }
                    else{
                        std::cout << "\033[31m" << "BLACK WINS" << "\033[0m" << std::endl;
                    }
                    break;
                }

                if(Grid.Is_Stalemate((Current_Player == 'W') ? 'B' : 'W')){
                    std::cout << "Stalemate — Draw!" << std::endl;
                    break;
                }

                Current_Player = (Current_Player == 'W') ? 'B' : 'W';
            }
            else{
                std::cout << "Inavlid Move" << std::endl;
            }
            continue;
        } 

        std::cin >> Pos_2;

        std::pair<int, int> Source = Convert_Input(Pos_1);
        std::pair<int, int> Destination = Convert_Input(Pos_2);

        if(Destination == Grid.Get_EP_Square() && Grid.Get_EP_Available()){
            bool Success = Grid.En_Passant(Source, Current_Player);

            if(Success){
                if(Grid.Is_Checkmate((Current_Player == 'W') ? 'B' : 'W')){
                    if(Current_Player == 'B'){
                        std::cout << "\033[32m" << "WHITE WINS!" << "\033[0m" << std::endl;
                    }
                    else{
                        std::cout << "\033[31m" << "BLACK WINS" << "\033[0m" << std::endl;
                    }
                    break;
                }

                if(Grid.Is_Stalemate((Current_Player == 'W') ? 'B' : 'W')){
                    std::cout << "Stalemate — Draw!" << std::endl;
                    break;
                }

                Current_Player = (Current_Player == 'W') ? 'B' : 'W';
            }
            else{
                std::cout << "Inavlid Move" << std::endl;
            }
            continue;

        }

        bool Success = Grid.Move_Piece(Source, Destination, Current_Player);

        if(Success){
            if(Grid.Is_Checkmate((Current_Player == 'W') ? 'B' : 'W')){
                if(Current_Player == 'B'){
                    std::cout << "\033[32m" << "WHITE WINS!" << "\033[0m" << std::endl;
                }
                else{
                    std::cout << "\033[31m" << "BLACK WINS" << "\033[0m" << std::endl;
                }
                break;
            }

            if(Grid.Is_Stalemate((Current_Player == 'W') ? 'B' : 'W')){
                std::cout << "Stalemate — Draw!" << std::endl;
                break;
            }

            Current_Player = (Current_Player == 'W') ? 'B' : 'W';
        }
        else{
            std::cout << "Inavlid Move" << std::endl;
        }
    }
}