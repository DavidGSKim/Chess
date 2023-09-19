#ifndef __KING_H__
#define __KING_H__
#include <string>
#include <iostream>
#include "Piece.h"
using namespace std;

class King : public Piece
{
private:
	bool canCastle();
	bool moved;

public:
	King(bool isW, char t, Pos p);
	~King();
	virtual bool validMove(int row, int col, Piece *allThePieces[8][8]) override; // Checks if a move is valid, returns status
	virtual bool inCheck(Piece *allThePieces[8][8]) override;
	virtual bool canRookCastle() override;
	bool validWithinBoard(int r, int c);
	bool isThereKnight(int newRow, int newCol, Piece *allThePiece[8][8]);
	bool isThereKing(int newRow, int newCol, Piece *allThePiece[8][8]);
};

#endif