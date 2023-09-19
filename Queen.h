#ifndef __QUEEN_H__
#define __QUEEN_H__
#include <string>
#include <iostream>
#include "Piece.h"
using namespace std;

class Queen : public Piece
{
public:
	~Queen();
	Queen(bool isW, char t, Pos p);
	virtual bool validMove(int row, int col, Piece *allThePieces[8][8]) override;
	virtual bool canRookCastle() override;
	virtual bool inCheck(Piece *allThePieces[8][8]) override;
	int abs(int val);
};

#endif