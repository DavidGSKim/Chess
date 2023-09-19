#ifndef __PIECE_H__
#define __PIECE_H__
#include <string>
#include <iostream>
using namespace std;

struct Pos
{
	int row;
	int column;
};

class Piece
{
protected:
	bool canCheckKing;
	static Piece *bKing;
	static Piece *wKing;

public:
	Pos position;
	bool isWhite;
	char type;
	bool enpassant;
	virtual ~Piece();
	Piece(Pos &po, bool isW, char t);
	void setPosition(int row, int col);
	virtual bool validMove(int row, int col, Piece *allThePieces[8][8]) = 0;
	virtual bool inCheck(Piece *allThePieces[8][8]) = 0;
	virtual bool canRookCastle() = 0;
	void setPieces(Piece *allPieces);
	char getType() const;
	bool getIsWhite() const;
};

#endif