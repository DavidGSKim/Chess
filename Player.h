#ifndef __PLAYER__
#define __PLAYER__
#include <string>
#include "GameBoard.h"

class Player
{
    bool white;
    bool human;

public:
    GameBoard *g;
    Player(bool isWhite);
    void setHuman(string isHuman);
    void setBoard(GameBoard &game);
    ~Player();
    void move(string curPos, string dest);
};

#endif
