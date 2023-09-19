#include <iostream>
#include "King.h"
#include "Player.h"

King::King(bool isW, char t, Pos p) : Piece{p, isW, t}, moved(false) {}

King::~King() {}

bool King::validWithinBoard(int r, int c)
{
	if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
	{
		return true;
	}
	return false;
}

bool King::inCheck(Piece *allThePiece[8][8])
{
	int curRow = position.row;
	int curCol = position.column;
	int newRow;
	int newCol;
	// see if opposite pawn attacking king
	if (isWhite)
	{
		// need to check if its valid within the board
		// cout << "mo" << endl;
		newRow = curRow - 1;
		newCol = curCol - 1;
		if (validWithinBoard(newRow, newCol))
		{
			// means either top left, or top right
			if (allThePiece[newRow][newCol] != nullptr && allThePiece[newRow][newCol]->getType() == 'p')
			{
				return true;
			}
		}
		newCol = curCol + 1;
		if (validWithinBoard(newRow, newCol))
		{
			// means either top left, or top right
			if (allThePiece[newRow][newCol] != nullptr && allThePiece[newRow][newCol]->getType() == 'p')
			{
				return true;
			}
		}
	}
	else
	{
		// need to check if its valid within the board
		newRow = curRow + 1;
		newCol = curCol - 1;
		if (validWithinBoard(newRow, newCol))
		{
			// means either top left, or top right
			if (allThePiece[newRow][newCol] != nullptr && allThePiece[newRow][newCol]->getType() == 'P')
			{
				return true;
			}
		}
		newCol = curCol + 1;
		if (validWithinBoard(newRow, newCol))
		{
			// means either top left, or top right
			if (allThePiece[newRow][newCol] != nullptr && allThePiece[newRow][newCol]->getType() == 'P')
			{
				return true;
			}
		}
	}

	// queen or rook up, down, left and right
	// see if opposing rooks
	// top
	for (int i = curRow - 1; i >= 0; i--)
	{
		Piece *p = allThePiece[i][curCol];
		if (p != nullptr)
		{
			if (this->isWhite && !p->isWhite && ((p->getType() == 'r') || (p->getType() == 'q')))
			{
				// king is white and the piece is black rook/queen
				return true;
			}
			else if (!this->isWhite && p->isWhite && ((p->getType() == 'R') || (p->getType() == 'Q')))
			{
				// king is black and the piece is a white rook/queen
				return true;
			}
			else
			{
				break;
			}
		}
	}
	// bottom
	for (int j = curRow + 1; j <= 7; j++)
	{
		Piece *p = allThePiece[j][curCol];
		if (p != nullptr)
		{
			if (this->isWhite && !p->isWhite && ((p->getType() == 'r') || (p->getType() == 'q')))
			{
				// king is white and the piece is black rook/queen
				return true;
			}
			else if (!this->isWhite && p->isWhite && ((p->getType() == 'R') || (p->getType() == 'Q')))
			{
				// king is black and the piece is a white rook/queen
				return true;
			}
			else
			{
				break;
			}
		}
	}
	// left
	for (int k = curCol - 1; k >= 0; k--)
	{
		Piece *p = allThePiece[curRow][k];
		if (p != nullptr)
		{
			if (this->isWhite && !p->isWhite && ((p->getType() == 'r') || (p->getType() == 'q')))
			{
				// king is white and the piece is black rook/queen
				return true;
			}
			else if (!this->isWhite && p->isWhite && ((p->getType() == 'R') || (p->getType() == 'Q')))
			{
				// king is black and the piece is a white rook/queen
				return true;
			}
			else
			{
				break;
			}
		}
	}
	// right
	for (int l = curCol + 1; l <= 7; l++)
	{
		Piece *p = allThePiece[curRow][l];
		if (p != nullptr)
		{
			if (this->isWhite && !p->isWhite && ((p->getType() == 'r') || (p->getType() == 'q')))
			{
				// king is white and the piece is black rook/queen
				return true;
			}
			else if (!this->isWhite && p->isWhite && ((p->getType() == 'R') || (p->getType() == 'Q')))
			{
				// king is black and the piece is a white rook/queen
				return true;
				
			}
			else
			{
				// same colour or some different piece
				break;
			}
		}
	}

	// check diagonals: bishop or queen
	int rowUp = curRow + 1;
	int rowDown = curRow - 1;
	// left top diagonal:
	for (int m = curCol - 1; m >= 0; m--)
	{
		if (validWithinBoard(rowUp, m))
		{
			Piece *p = allThePiece[rowUp][m];
			if (p != nullptr)
			{
				if (this->isWhite && ((p->getType() == 'b') || (p->getType() == 'q')))
				{
					// king is white, either black bishop or queen
					return true;
				}
				else if (!this->isWhite && ((p->getType() == 'B') || (p->getType() == 'Q')))
				{
					// black king with either a white bishop or queen
					return true;
				}
				else
				{
					break;
				}
			}
			++rowUp;
		}
		else
		{
			break;
		}
	}
	// left bottom diagonal:
	for (int n = curCol - 1; n >= 0; n--)
	{
		if (validWithinBoard(rowDown, n))
		{
			Piece *p = allThePiece[rowDown][n];
			if (p != nullptr)
			{
				if (this->isWhite && ((p->getType() == 'b') || (p->getType() == 'q')))
				{
					// king is white, either black bishop or queen
					return true;
				}
				else if (!this->isWhite && ((p->getType() == 'B') || (p->getType() == 'Q')))
				{
					// black king with either a white bishop or queen
					return true;
				}
				else
				{
					break;
				}
			}
			--rowDown;
		}
		else
		{
			break;
		}
	}

	rowUp = curRow + 1;
	rowDown = curRow - 1;
	// right top diagonal:
	for (int o = curCol + 1; o <= 7; o++)
	{
		if (validWithinBoard(rowUp, o))
		{
			Piece *p = allThePiece[rowUp][o];
			if (p != nullptr)
			{
				if (this->isWhite && ((p->getType() == 'b') || (p->getType() == 'q')))
				{
					// king is white, either black bishop or queen
					return true;
				}
				else if (!this->isWhite && ((p->getType() == 'B') || (p->getType() == 'Q')))
				{
					// black king with either a white bishop or queen
					return true;
				}
				else
				{
					break;
				}
			}
			++rowUp;
		}
		else
		{
			break;
		}
	}
	// right bottom diaongal:
	for (int q = curCol + 1; q <= 7; q++)
	{
		if (validWithinBoard(rowDown, q))
		{

			Piece *p = allThePiece[rowDown][q];
			if (p != nullptr)
			{
				if (this->isWhite && ((p->getType() == 'b') || (p->getType() == 'q')))
				{
					// king is white, either black bishop or queen
					return true;
				}
				else if (!this->isWhite && ((p->getType() == 'B') || (p->getType() == 'Q')))
				{
					// black king with either a white bishop or queen
					return true;
				}
				else
				{
					break;
				}
			}
			--rowDown;
		}
		else
		{
			break;
		}
	}

	// check knight:
	// the first position:
	newRow = curRow - 2;
	newCol = curCol + 1;
	if (isThereKnight(newRow, newCol, allThePiece))
	{
		return true;
	}
	// 2nd position:
	newRow = curRow - 1;
	newCol = curCol + 2;
	if (isThereKnight(newRow, newCol, allThePiece))
	{
		return true;
	}
	// 3rd position:
	newRow = curRow + 1;
	newCol = curCol + 2;
	if (isThereKnight(newRow, newCol, allThePiece))
	{
		return true;
	}
	// 4th position:
	newRow = curRow + 2;
	newCol = curCol + 1;
	if (isThereKnight(newRow, newCol, allThePiece))
	{
		return true;
	}
	// 5th position:
	newRow = curRow + 2;
	newCol = curCol - 1;
	if (isThereKnight(newRow, newCol, allThePiece))
	{
		return true;
	}
	// 6th position
	newRow = curRow + 1;
	newCol = curCol - 2;
	if (isThereKnight(newRow, newCol, allThePiece))
	{
		return true;
	}
	// 7th position
	newRow = curRow - 1;
	newCol = curCol - 2;
	if (isThereKnight(newRow, newCol, allThePiece))
	{
		return true;
	}
	// 8th position
	newRow = curRow - 2;
	newCol = curCol - 1;
	if (isThereKnight(newRow, newCol, allThePiece))
	{
		return true;
	}

	// check other king:
	//top left
	newRow = curRow - 1;
	newCol = curCol - 1;
	if (isThereKing(newRow, newCol, allThePiece))
	{
		return true;
	}
	// top
	newRow = curRow - 1;
	newCol = curCol;
	if (isThereKing(newRow, newCol, allThePiece))
	{
		return true;
	}
	// top right
	newRow = curRow - 1;
	newCol = curCol + 1;
	if (isThereKing(newRow, newCol, allThePiece))
	{
		return true;
	}
	// left
	newRow = curRow;
	newCol = curCol - 1;
	if (isThereKing(newRow, newCol, allThePiece))
	{
		return true;
	}
	// right
	newRow = curRow;
	newCol = curCol + 1;
	if (isThereKing(newRow, newCol, allThePiece))
	{
		return true;
	}
	// bottom left
	newRow = curRow + 1;
	newCol = curCol - 1;
	if (isThereKing(newRow, newCol, allThePiece))
	{
		return true;
	}
	// bottom
	newRow = curRow + 1;
	newCol = curCol;
	if (isThereKing(newRow, newCol, allThePiece))
	{
		return true;
	}
	// bottom right
	newRow = curRow + 1;
	newCol = curCol + 1;
	if (isThereKing(newRow, newCol, allThePiece))
	{
		return true;
	}

	return false;
}

bool King::isThereKing(int newRow, int newCol, Piece *allThePiece[8][8])
{
	if (validWithinBoard(newRow, newCol))
	{
		Piece *p = allThePiece[newRow][newCol];
		if (p != nullptr)
		{
			if (this->isWhite && p->getType() == 'k')
			{
				// white king with a black king on board
				return true;
			}
			else if (!this->isWhite && p->getType() == 'K')
			{
				// black king with a white king on square
				return true;
			}
		}
	}
	return false;
}
bool King::isThereKnight(int newRow, int newCol, Piece *allThePiece[8][8])
{
	if (validWithinBoard(newRow, newCol))
	{
		Piece *p = allThePiece[newRow][newCol];
		if (p != nullptr)
		{
			if (this->isWhite && p->getType() == 'n')
			{
				// white king with a black king on board
				return true;
			}
			else if (!this->isWhite && p->getType() == 'N')
			{
				// black king wiht a white king on square
				return true;
			}
		}
	}
	return false;
}

bool King::validMove(int row, int col, Piece *allThePieces[8][8])
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

	if ((col == curCol + 1) && (row == curRow + 1))
	{
		moved = true;
		return true;
	}
	else if ((col == curCol + 1) && (row == curRow))
	{
		moved = true;
		return true;
	}
	else if ((col == curCol) && (row == curRow + 1))
	{
		moved = true;
		return true;
	}
	else if ((col == curCol - 1) && (row == curRow - 1))
	{
		moved = true;
		return true;
	}
	else if ((col == curCol - 1) && (row == curRow + 1))
	{
		moved = true;
		return true;
	}
	else if ((col == curCol + 1) && (row == curRow - 1))
	{
		moved = true;
		return true;
	}
	else if ((col == curCol) && (row == curRow - 1))
	{
		moved = true;
		return true;
	}
	else if ((col == curCol - 1) && (row == curRow))
	{
		moved = true;
		return true;
	} // Implementing castling, left (queenside)
	else if ((moved == false) && (allThePieces[curRow][curCol - 1] == nullptr) && (allThePieces[curRow][curCol - 2] == nullptr) && (allThePieces[curRow][curCol - 3] == nullptr) && (col == curCol - 2) && (row == curRow))
	{
		// see if rook has moved: the left most ones
		if ((allThePieces[row][0] != nullptr) && (((allThePieces[row][0]->getType() == 'R') && (this->getType() == 'K')) || ((allThePieces[row][0]->getType() == 'r') && (this->getType() == 'k'))))
		{
			// make sure u cannot castle out of check!!
			if (inCheck(allThePieces))
			{
				return false;
			}

			if (!allThePieces[row][0]->canRookCastle())
			{
				return false;
			}
			else
			{
				moved = true;
				return true;
			}
		}
	} // Implementing castling, right (kingside)
	else if ((moved == false) && (allThePieces[curRow][curCol + 1] == nullptr) && (allThePieces[curRow][curCol + 2] == nullptr) && (col == curCol + 2) && (row == curRow))
	{
		// see if rook has moved: the right most ones
		if ((allThePieces[row][7] != nullptr) && (((allThePieces[row][7]->getType() == 'R') && (this->getType() == 'K')) || ((allThePieces[row][7]->getType() == 'r') && (this->getType() == 'k'))))
		{
			// make sure u cannot castle out of check!!
			if (inCheck(allThePieces))
			{
				return false;
			}

			if (!allThePieces[row][7]->canRookCastle())
			{
				return false;
			}
			else
			{
				moved = true;
				return true;
			}
		}
	}
	return false;
}

bool King::canRookCastle()
{
	return false;
}
