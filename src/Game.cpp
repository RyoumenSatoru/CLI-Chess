#include "Game.h"
#include "utils/Utils.h"

Game::Game() {
    Grid.Initialize();
    Current_Player = 'W';
}

bool Game::Check_Game_Over(char Player) {
    if (Grid.Is_Checkmate(Player)) {
        system("clear");
        Grid.Print_Board(Player == 'B');

        if (Player == 'W') {
            std::cout << "\033[31m" << "Checkmate!\nBlack Wins!" << "\033[0m" << std::endl;
        } else {
            std::cout << "\033[32m" << "Checkmate!\nWhite Wins!" << "\033[0m" << std::endl;
        }
        return true;
    }

    if (Grid.Is_Stalemate(Player)) {
        system("clear");
        Grid.Print_Board(Player == 'B');
        std::cout << "Stalemate! It's a Draw!" << std::endl;
        return true;
    }

    return false;
}

static char Switch_Player(char Player) {
    return (Player == 'W') ? 'B' : 'W';
}

void Game::Run() {
    std::string Message = "";

    while (true) {
        system("clear");
        Grid.Print_Board(Current_Player == 'W');
        std::cout << Message << std::endl;

        std::pair<int, int> King_Position = Grid.Get_King_Position(Current_Player);
        if (Grid.Is_In_Check(Current_Player, King_Position)) {
            std::string Check_Color = (Current_Player == 'W') ? "\033[31m" : "\033[32m";
            std::cout << Check_Color << "Check!" << "\033[0m" << std::endl;
        }

        std::string Player_Name = (Current_Player == 'W') ? "White" : "Black";
        std::cout << Player_Name << "'s Move: ";

        std::string Pos_1, Pos_2;
        std::cin >> Pos_1;

        if (Pos_1 == "0-0") {
            bool Success = Grid.Castling(true, Current_Player);
            Message = Success ? "" : "Invalid castling move — try again.";
            if (Success) {
                if (Check_Game_Over(Switch_Player(Current_Player))) break;
                Current_Player = Switch_Player(Current_Player);
            }
            std::cout << Message << std::endl;
            continue;
        }

        if (Pos_1 == "0-0-0") {
            bool Success = Grid.Castling(false, Current_Player);
            Message = Success ? "" : "Invalid castling move — try again.";
            if (Success) {
                if (Check_Game_Over(Switch_Player(Current_Player))) break;
                Current_Player = Switch_Player(Current_Player);
            }
            std::cout << Message << std::endl;
            continue;
        }

        std::cin >> Pos_2;

        std::pair<int, int> Source      = Convert_Input(Pos_1);
        std::pair<int, int> Destination = Convert_Input(Pos_2);

        if (Source.first == -1 || Destination.first == -1) {
            Message = "Couldn't understand that square — use format like E2 E4.";
            std::cout << Message << std::endl;
            continue;
        }

        if (Grid.Get_EP_Available() && Destination == Grid.Get_EP_Square()) {
            bool Success = Grid.En_Passant(Source, Current_Player);
            Message = Success ? "" : "Invalid en passant — try again.";
            if (Success) {
                if (Check_Game_Over(Switch_Player(Current_Player))) break;
                Current_Player = Switch_Player(Current_Player);
            }
            std::cout << Message << std::endl;
            continue;
        }

        bool Success = Grid.Move_Piece(Source, Destination, Current_Player);
        Message = Success ? "" : "Invalid move — that piece can't go there.";
        if (Success) {
            if (Check_Game_Over(Switch_Player(Current_Player))) break;
            Current_Player = Switch_Player(Current_Player);
        }
    }
}