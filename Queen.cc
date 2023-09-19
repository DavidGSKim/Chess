#include <iostream>
#include "Queen.h"
using namespace std;

Queen::Queen(bool isW, char t, Pos p) : Piece{p, isW, t} {}

Queen::~Queen() {}

// Checks if move is valid
bool Queen::validMove(int row, int col, Piece *allThePieces[8][8])
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
	if ((curRow == row && curCol == col) || !capture)
		return false;

	// Moving left or right
	if ((curRow == row) || (curCol == col))
	{
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
						return true;
					}
					if (!(allThePieces[row][curCol] == nullptr))
						break;
				}
			} // moving left
			else if (curCol > col)
			{
				while (true)
				{
					curCol--;
					if (curCol == col)
					{
						return true;
					}
					if (!(allThePieces[row][curCol] == nullptr))
						break;
				}
			}
		}
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
						return true;
					}
					if (!(allThePieces[curRow][col] == nullptr))
						break;
				}
			} // moving up
			else if (curRow > row)
			{
				while (true)
				{
					curRow--;
					if (curRow == row)
					{
						return true;
					}
					if (!(allThePieces[curRow][col] == nullptr))
						break;
				}
			}
		}
		// Moving diagonally
	}
	else if (abs(curCol - col) == abs(curRow - row))
	{
		if (curCol < col && curRow < row)
		{
			// negaitve linear starting from origin
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
			// positive linear starting from end
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
			// positive linear starting from origin
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
			// positive linear starting from end
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
	}
	return false;
}

int Queen::abs(int val)
{
	if (val < 0)
		return -val;
	else
		return val;
}

bool Queen::canRookCastle()
{
	return false;
}
bool Queen::inCheck(Piece *allThePieces[8][8])
{
	return false;
}