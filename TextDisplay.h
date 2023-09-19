#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <string>
#include "GameBoard.h"
using namespace std;
class GameBoard;

class TextDisplay
{
    GameBoard *b;

public:
    TextDisplay();
    void setBoard(GameBoard &g);
    friend std::ostream &operator<<(std::ostream &out, TextDisplay &g);
    ~TextDisplay();
};

#endif