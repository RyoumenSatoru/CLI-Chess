#include "Game.h"
#include "utils/Utils.h"

Game::Game(){
    Grid.Initialize();
    Current_Player = 'W';
}

bool Game::Check_Game_Over(char Player){
    if(Grid.Is_Checkmate(Player)){
        if(Player == 'W'){
            std::cout << "\033[31m" << "Black Wins!" << "\033[0m" << std::endl;
        }
        else{
            std::cout << "\033[32m" << "White Wins!" << "\033[0m" << std::endl;
        }

        return true;
    }
    if(Grid.Is_Stalemate(Player)){
        std::cout << "Stalemate! -- Draw!" << std::endl;
        return true;
    }
    return false;
}

void Game::Run(){
    while(true){
        Grid.Print_Board((Current_Player == 'W'));

        std::pair<int, int> King_Position = (Current_Player == 'W') ? Grid.Get_King_Position('W') : Grid.Get_King_Position('B');

        if(Grid.Is_In_Check(Current_Player, King_Position)){
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
        std::cin >> Pos_1;

        if(Pos_1 == "0-0"){
            bool Success = Grid.Castling(true, Current_Player);
            if(Success){
                bool Game_Over = Check_Game_Over((Current_Player == 'W') ? 'B' : 'W');
                if(Game_Over){
                    break;
                }
                Current_Player = (Current_Player == 'W') ? 'B' : 'W';
            }
            else{
                std::cout << "Invalid Move!" << std::endl;
            }
            continue;
        }

        if(Pos_1 == "0-0-0"){
            bool Success = Grid.Castling(false, Current_Player);
            if(Success){
                bool Game_Over = Check_Game_Over((Current_Player == 'W') ? 'B' : 'W');
                if(Game_Over){
                    break;
                }
                Current_Player = (Current_Player == 'W') ? 'B' : 'W';
            }
            else{
                std::cout << "Invalid Move!" << std::endl;
            }
            continue;
        }

        std::cin >> Pos_2;

        std::pair<int, int> Source = Convert_Input(Pos_1);
        std::pair<int, int> Destination = Convert_Input(Pos_2);

        if(Source.first == -1 || Destination.first == -1){
            std::cout << "Invalid Move!" << std::endl;
            continue;
        }

        if(Destination == Grid.Get_EP_Square() && Grid.Get_EP_Available()){
            bool Success = Grid.En_Passant(Source, Current_Player);
            if(Success){
                bool Game_over = Check_Game_Over((Current_Player == 'W') ? 'B' : 'W');
                if(Game_over){
                    break;
                }
                Current_Player = (Current_Player == 'W') ? 'B' : 'W';
            }
            else{
                std::cout << "Invalid Move" << std::endl;
            }
            continue;
        }

        bool Success = Grid.Move_Piece(Source, Destination, Current_Player);
        if(Success){
            bool Game_Over = Check_Game_Over((Current_Player == 'W') ? 'B' : 'W');
            if(Game_Over){
                break;
            }
            Current_Player = (Current_Player == 'W') ? 'B' : 'W';
        }
        else{
            std::cout << "Invalid Move" << std::endl;
        }
    }
}