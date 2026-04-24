#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game{
private:
    Board Grid;
    char Current_Player;
    

public:
    Game();
    void Run();
    bool Check_Game_Over(char Player);
};

#endif