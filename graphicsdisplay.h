#include "window.h"
#include <string>
#ifndef _GRAPHICSDISPLAY_H
#define _GRAPHICSDISPLAY_H
class GameBoard;
using namespace std;
class GraphicsDisplay
{
	GameBoard *b;
	char board[8][8];
	int size;
	int Xoffset;
	int Yoffset;

public:
	Xwindow w1;
	GraphicsDisplay(int);
	void initBoard(GameBoard *);
	void update(Xwindow &disp, int sRow, int sCol, int eRow, int eCol);
	void drawBoard(Xwindow &);
};
#endif