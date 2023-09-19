#include <iostream>
#include "Pawn.h"
using namespace std;

// Pawn::Pawn( char l):Piece(l) {}
Pawn::Pawn(bool isW, char t, Pos p) : Piece{p, isW, t} {}

Pawn::~Pawn() {}

void Pawn::canEnpassant() {}

bool Pawn::validWithinBoard(int r, int c)
{
	if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
	{
		return true;
	}
	return false;
}
bool Pawn::validMove(int row, int col, Piece *allThePieces[8][8])
{
	int curRow = position.row;
	int curCol = position.column;
	int BoardSize = 7;
	string colour;
	if (allThePieces[curRow][curCol]->isWhite)
	{
		colour = "white";
	}
	else
	{
		colour = "black";
	}

	bool capture = (row <= BoardSize && row >= 0 &&
					col <= BoardSize && col >= 0 &&
					(allThePieces[row][col] == nullptr || (colour == "white" && allThePieces[row][col]->isWhite == false) || (colour == "black" && allThePieces[row][col]->isWhite == true)));
	if ((curRow == row && curCol == col) || !capture)
	{
		return false;
	}

	if (colour == "white")
	{
		// moving left
		if (validWithinBoard(curRow - 1, curCol - 1) && (curRow - 1 == row) && (curCol - 1 == col) && (allThePieces[curRow - 1][curCol - 1] == nullptr) &&
			(allThePieces[curRow][curCol - 1] != nullptr) &&
			(allThePieces[curRow][curCol - 1]->getType() == 'p') && (allThePieces[curRow][curCol - 1]->enpassant == true))
		{
			return true;
		}
		else if (validWithinBoard(curRow - 1, curCol + 1) && (curRow - 1 == row) && (curCol + 1 == col) && (allThePieces[curRow - 1][curCol + 1] == nullptr) &&
				 (allThePieces[curRow][curCol + 1] != nullptr) &&
				 (allThePieces[curRow][curCol + 1]->getType() == 'p') && (allThePieces[curRow][curCol + 1]->enpassant == true))
		{
			return true;
		}
	}
	else if (colour == "black")
	{
		// moving left
		if (validWithinBoard(curRow + 1, curCol - 1) && (curRow + 1 == row) && (curCol - 1 == col) && (curRow - 1 == row) && (curCol - 1 == col) && (allThePieces[curRow + 1][curCol - 1] == nullptr) &&
			(allThePieces[curRow][curCol - 1] != nullptr) &&
			(allThePieces[curRow][curCol - 1]->getType() == 'P') && (allThePieces[curRow][curCol - 1]->enpassant == true))
		{
			return true;
		} // moving right
		else if (validWithinBoard(curRow + 1, curCol + 1) && (curRow + 1 == row) && (curCol + 1 == col) && (allThePieces[curRow + 1][curCol + 1] == nullptr) &&
				 (allThePieces[curRow][curCol + 1] != nullptr) &&
				 (allThePieces[curRow][curCol + 1]->getType() == 'P') && (allThePieces[curRow][curCol + 1]->enpassant == true))
		{
			return true;
		}
	}
	if (colour == "white")
	{
		// Note that moving forward for white is moving down in rows
		// capture diagonally left or right
		if ((allThePieces[row][col] != nullptr) && !(allThePieces[row][col]->isWhite) && ((row == curRow - 1) && ((col == curCol + 1) || (col == curCol - 1))))
		{
			enpassant = false;
			return true;
		}
		else if (allThePieces[row][col] == nullptr && row == curRow - 1)
		{
			enpassant = false;
			return true;
		}
		else if ((curRow == 6) && ((row == curRow - 1) || (row == curRow - 2)))
		{
			enpassant = true;
			return true;
		}
	}
	else
	{
		//capture diagonally left or right
		if ((allThePieces[row][col] != nullptr) && (allThePieces[row][col]->isWhite) && ((row == curRow + 1) && ((col == curCol + 1) || (col == curCol - 1))))
		{
			enpassant = false;
			return true;
		}
		else if (allThePieces[row][col] == nullptr && row == curRow + 1)
		{
			enpassant = false;
			return true;
		}
		else if (((curRow == 1) && (row == curRow + 1)) || (row == curRow + 2))
		{
			enpassant = true;
			return true;
		}
	}
	return false;
}

bool Pawn::canRookCastle()
{
	return false;
}
bool Pawn::inCheck(Piece *allThePieces[8][8])
{
	return false;
}