#include <iostream>
#include "Bishop.h"
#include "Piece.h"
using namespace std;

Bishop::Bishop(bool isW, char t, Pos p) : Piece(p, isW, t) {}

Bishop::~Bishop() {}

bool Bishop::canRookCastle()
{
	return false;
}
bool Bishop::inCheck(Piece *allThePieces[8][8])
{
	return false;
}

int Bishop::abs(int val)
{
	if (val < 0)
		return -val;
	else
		return val;
}

bool Bishop::validMove(int row, int col, Piece *allThePieces[8][8])
{
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
					(allThePieces[row][col] == nullptr || (colour == "white" && allThePieces[row][col]->isWhite == false) || (colour == "black" && allThePieces[row][col]->isWhite == true)));
	if ((curRow == row && curCol == col) || !capture || abs(curCol - col) != abs(curRow - row))
		return false;
	if (curCol < col && curRow < row)
	{
		// moving bottom right
		while (true)
		{
			curRow++;
			curCol++;
			if (curCol == col)
			{
				return true;
			}
			if (!(allThePieces[curRow][curCol] == nullptr))
				break;
		}
	}
	else if (curCol > col && curRow > row)
	{
		// moving top left
		while (true)
		{
			curRow--;
			curCol--;
			if (curCol == col)
			{
				return true;
			}
			if (!(allThePieces[curRow][curCol] == nullptr))
				break;
		}
	}
	else if (curCol < col && curRow > row)
	{
		// moving top right
		while (true)
		{
			curRow--;
			curCol++;
			if (curCol == col)
			{
				return true;
			}
			if (!(allThePieces[curRow][curCol] == nullptr))
				break;
		}
	}
	else if (curCol > col && curRow < row)
	{
		// moving bottom left
		while (true)
		{
			curRow++;
			curCol--;
			if (curCol == col)
			{
				return true;
			}
			if (!(allThePieces[curRow][curCol] == nullptr))
				break;
		}
	}
	return false;
}
