#ifndef __ROOK_H__
#define __ROOK_H_H__
#include <string>
#include <iostream>
#include "Piece.h"
using namespace std;

class Rook : public Piece
{
private:
public:
	bool canCastle;
	~Rook();
	Rook(bool isW, char t, Pos p);
	virtual bool validMove(int row, int col, Piece *allThePieces[8][8]) override;
	virtual bool canRookCastle() override;
	virtual bool inCheck(Piece *allThePieces[8][8]) override;
};

#endif