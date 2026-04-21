#include "Board.h"
#include "Piece.h"

pair<int, int> Convert_Input(string Position){
    char File = toupper(Position[0]);
    int Col = File - 'A';

    int Row = 8 - (Position[1] - '0');

    return {Row, Col};
}

int main() {
    Board Chess;

    int Iterator = 0;
    int Win = 0;

    string Pos_1, Pos_2;

    while(Win == 0){
        if(Iterator%2 == 0){
            Chess.Print_Board(true);
            
            cout << "White's Move: ";
            cin >> Pos_1 >> Pos_2;
            
            pair<int, int> Source = Convert_Input(Pos_1);
            pair<int, int> Destination = Convert_Input(Pos_2);

            Chess.Move_Piece(Source, Destination);
            
        }
        else{
            Chess.Print_Board(false);
            
            cout << "Black's Move: ";
            cin >> Pos_1 >> Pos_2;

            pair<int, int> Source = Convert_Input(Pos_1);
            pair<int, int> Destination = Convert_Input(Pos_2);

            Chess.Move_Piece(Source, Destination);
        }
        Iterator++;
    }

    return 0;
}