#include <iostream>
#include "Rook.h"
#include <iomanip>
#include <string>
using namespace std;

Rook::Rook(bool isW, char t, Pos p) : Piece(p, isW, t), canCastle(true) {}

Rook::~Rook() {}

bool Rook::canRookCastle()
{
	return canCastle;
}

bool Rook::inCheck(Piece *allThePieces[8][8])
{
	return false;
}

// Checks if move is valid to move to the row and col
bool Rook::validMove(int row, int col, Piece *allThePieces[8][8])
{
	Pos position = this->position;
	int curRow = position.row;
	int curCol = position.column;
	int BoardSize = 7;
	string colour;
	if (allThePieces[curRow][curCol]->isWhite)
		colour = "white";
	else
		colour = "black";

	bool capture = (row <= BoardSize && row >= 0 &&
					col <= BoardSize && col >= 0 &&
					(allThePieces[row][col] == nullptr ||
					 (colour == "white" && allThePieces[row][col]->isWhite == false) ||
					 (colour == "black" && allThePieces[row][col]->isWhite == true)));
	if ((curRow == row && curCol == col) || !capture)
		return false;
	// move left/right
	if (curRow == row)
	{
		// moving right
		if (curCol < col)
		{
			while (true)
			{
				curCol++;
				if (curCol == col)
				{
					canCastle = false;
					return true;
				}
				if (!(allThePieces[row][curCol] == nullptr))
					break;
			}
		}
		// moving left
		else if (curCol > col)
		{
			while (true)
			{
				curCol--;
				if (curCol == col)
				{
					canCastle = false;
					return true;
				}
				if (!(allThePieces[row][curCol] == nullptr))
					break;
			}
		}
	}
	// moves up/down
	else if (curCol == col)
	{
		// moving down
		if (curRow < row)
		{
			while (true)
			{
				curRow++;
				if (curRow == row)
				{
					canCastle = false;
					return true;
				}
				if (!(allThePieces[curRow][col] == nullptr))
					break;
			}
		}
		// moving up
		else if (curRow > row)
		{
			while (true)
			{
				curRow--;
				if (curRow == row)
				{
					canCastle = false;
					return true;
				}
				if (!(allThePieces[curRow][col] == nullptr))
					break;
			}
		}
	}
	return false;
}