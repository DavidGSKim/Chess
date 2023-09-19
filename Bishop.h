#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <string>
#include <iostream>
#include "Piece.h"
using namespace std;

class Bishop : public Piece
{
public:
	~Bishop();
	Bishop(bool isW, char t, Pos p);
	virtual bool validMove(int row, int col, Piece *allThePieces[8][8]) override;
	virtual bool canRookCastle() override;
	virtual bool inCheck(Piece *allThePieces[8][8]) override;
	int abs(int val);
};

#endif