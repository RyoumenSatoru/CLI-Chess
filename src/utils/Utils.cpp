#include "Utils.h"

std::pair<int, int> Convert_Input(std::string Position){
    if(Position.length() < 2){
        std::cout << "Invalid input format" << std::endl;
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