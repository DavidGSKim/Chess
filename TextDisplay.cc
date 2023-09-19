#include "TextDisplay.h"
#include <sstream>
#include <iostream>
#include "Piece.h"
#include "GameBoard.h"
using namespace std;

TextDisplay::TextDisplay(){};

TextDisplay::~TextDisplay(){};

void TextDisplay::setBoard(GameBoard &g)
{
    b = &g;
}

ostream &operator<<(std::ostream &out, TextDisplay &g)
{
    int leftNum = 8;
    // print top to bottom, left to right
    for (int i = 0; i <= 7; i++)
    {
        // prints out the number
        out << leftNum;
        out << " ";
        for (int j = 0; j <= 7; j++)
        {
            Piece *p = g.b->gameBoard[i][j];
            if (p != nullptr)
            {
                out << p->getType();
            }
            else if ((i + j) % 2 != 0)
            {
                out << '-';
            }
            else
            {
                out << ' ';
            }
        }
        out << endl;
        --leftNum;
    }
    out << endl;
    out << "  abcdefgh" << endl;
    return out;
}