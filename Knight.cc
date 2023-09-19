#include <iostream>
#include "Knight.h"
using namespace std;

Knight::Knight(bool isW, char t, Pos p) : Piece{p, isW, t} {}

Knight::~Knight() {}

// Checks if move is valid
bool Knight::validMove(int row, int col, Piece *allThePieces[8][8])
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
					(allThePieces[row][col] == nullptr || (colour == "white" && allThePieces[row][col]->isWhite == false) ||
					 (colour == "black" && allThePieces[row][col]->isWhite == true)));
	if ((curRow == row && curCol == col) || !capture)
		return false;

	if ((col == curCol + 1) && (row == curRow + 2) && capture)
	{
		return true;
	}
	else if ((col == curCol + 2) && (row == curRow + 1) && capture)
	{
		return true;
	}
	else if ((col == curCol - 1) && (row == curRow - 2) && capture)
	{
		return true;
	}
	else if ((col == curCol - 2) && (row == curRow - 1) && capture)
	{
		return true;
	}
	else if ((col == curCol - 1) && (row == curRow + 2) && capture)
	{
		return true;
	}
	else if ((col == curCol + 2) && (row == curRow - 1) && capture)
	{
		return true;
	}
	else if ((col == curCol + 1) && (row == curRow - 2) && capture)
	{
		return true;
	}
	else if ((col == curCol - 2) && (row == curRow + 1) && capture)
	{
		return true;
	}
	return false;
}

bool Knight::canRookCastle()
{
	return false;
}
bool Knight::inCheck(Piece *allThePieces[8][8])
{
	return false;
}