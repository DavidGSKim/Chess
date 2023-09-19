#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <string>
#include <iostream>
#include "Piece.h"
using namespace std;

class Knight : public Piece
{
public:
	~Knight();
	Knight(bool isW, char t, Pos p);
	virtual bool validMove(int row, int col, Piece *allThePieces[8][8]) override;
	virtual bool canRookCastle() override;
	virtual bool inCheck(Piece *allThePieces[8][8]) override;
};

#endif