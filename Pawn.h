#ifndef __PAWN_H__
#define __PAWN_H__
#include <string>
#include <iostream>
#include "Piece.h"
using namespace std;

class Pawn : public Piece
{
private:
public:
	~Pawn();
	Pawn(bool isW, char t, Pos p);
	virtual bool canRookCastle() override;
	virtual bool validMove(int row, int col, Piece *allThePieces[8][8]) override;
	virtual bool inCheck(Piece *allThePieces[8][8]) override;
	bool validWithinBoard(int r, int c);
	void canEnpassant();
};

#endif