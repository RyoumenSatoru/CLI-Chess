#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <utility>

class Piece{
protected:
    char Color;
    std::pair<int, int> Current_Position;
public:
    Piece(char Colour, std::pair<int, int> Starting_Position) : Color(Colour), Current_Position(Starting_Position) {}

    virtual char Get_Symbol() = 0;
    char Get_Color(){
        return Color;
    }
    std::pair<int, int> Get_Position(){
        return Current_Position;
    }
    virtual void Display_Symbol(){
        if(Get_Color() == 'W'){
            std::cout << "\033[32m" << Get_Symbol() << "\033[0m ";
        }
        else{
            std::cout << "\033[31m" << Get_Symbol() << "\033[0m ";
        }
    }
};

#endif