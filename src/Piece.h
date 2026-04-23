#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <utility>
#include <algorithm>
#include <cmath>

class Piece{
protected:
    char Color;
    std::pair<int, int> Current_Position;
    bool Has_Moved;
public:
    Piece(char Colour, std::pair<int, int> Starting_Position) : Color(Colour), Current_Position(Starting_Position), Has_Moved(false) {}

    virtual char Get_Symbol() = 0;
    
    char Get_Color(){
        return Color;
    }

    std::pair<int, int> Get_Position(){
        return Current_Position;
    }

    virtual void Display_Symbol(){
        if(Get_Color() == 'W'){
            std::cout << "\033[32m " << Get_Symbol() << "\033[0m ";
        }
        else{
            std::cout << "\033[31m " << Get_Symbol() << "\033[0m ";
        }
    }

    void Set_Position(std::pair<int ,int> New_Position){
        Current_Position = New_Position;
    }

    virtual bool Is_Valid_Move(std::pair<int, int> Destination, Piece* Board[8][8]) = 0;

    bool Get_Has_Moved(){
        return Has_Moved;
    }

    void Set_Has_Moved(){
        Has_Moved = true;
    }
};

#endif