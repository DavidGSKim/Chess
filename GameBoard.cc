#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>
#include "GameBoard.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Player.h"
#include "TextDisplay.h"

int GameBoard::getCorrRow(int c)
{
	return 8 - c;
}

int GameBoard::getCorrCol(char c)
{
	return c - 'a';
}

void GameBoard::placePiece(bool isWhite, char piece, int row, int col)
{
	// deletes the piece that is located there
	Piece *oldPiece = gameBoard[row][col];
	delete oldPiece;
	if (piece == 'p' || piece == 'P')
	{
		Piece *newPiece = new Pawn(isWhite, piece, Pos{row, col});
		gameBoard[row][col] = newPiece;
	}
	else if (piece == 'r' || piece == 'R')
	{
		Piece *newPiece = new Rook(isWhite, piece, Pos{row, col});
		gameBoard[row][col] = newPiece;
	}
	else if (piece == 'n' || piece == 'N')
	{
		Piece *newPiece = new Knight(isWhite, piece, Pos{row, col});
		gameBoard[row][col] = newPiece;
	}
	else if (piece == 'b' || piece == 'B')
	{
		Piece *newPiece = new Bishop(isWhite, piece, Pos{row, col});
		gameBoard[row][col] = newPiece;
	}
	else if (piece == 'q' || piece == 'Q')
	{
		Piece *newPiece = new Queen(isWhite, piece, Pos{row, col});
		gameBoard[row][col] = newPiece;
	}
	else if (piece == 'k' || piece == 'K')
	{
		Piece *newPiece = new King(isWhite, piece, Pos{row, col});
		gameBoard[row][col] = newPiece;
	}
}

void GameBoard::deletePiece(int row, int col)
{
	if (gameBoard[row][col] != nullptr)
	{
		delete gameBoard[row][col];
		gameBoard[row][col] = nullptr;
	}
}

bool GameBoard::isWhiteTurn()
{
	return isWhiteMove;
}

// returns the coordinates of where the king is located
string GameBoard::getKing(bool isWhite)
{
	string result;
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			Piece *p = gameBoard[i][j];
			if (p != nullptr)
			{
				if (isWhite && p->getType() == 'K')
				{
					// is white = means it's white's turn
					string theRow = to_string(i);
					string theCol = to_string(j);
					return theRow + theCol;
				}
				else if (!isWhite && p->getType() == 'k')
				{
					// is black = means black king
					string theRow = to_string(i);
					string theCol = to_string(j);
					return theRow + theCol;
				}
			}
		}
	}
	return result;
}

bool GameBoard::validCoord(int num)
{
	if (num >= 0 && num <= 7)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// assumes the king is already in check. sees if it is checkmate (no more valid moves)
bool GameBoard::inCheckmate(bool isWhite)
{
	string kingPos = getKing(isWhite);
	int kingCurrRow = kingPos[0] - '0';
	int kingCurrCol = kingPos[1] - '0';
	Piece *king = gameBoard[kingCurrRow][kingCurrCol];
	int checks = 0;
	if (king->validMove(kingCurrRow + 1, kingCurrCol + 1, gameBoard))
	{
		Piece *newKing = new King(king->isWhite, king->getType(), Pos{kingCurrRow + 1, kingCurrCol + 1});
		if (newKing->inCheck(gameBoard))
		{
			// cannot move to position
			++checks;
		}
		delete newKing;
	}
	else
	{
		++checks;
	}

	if (king->validMove(kingCurrRow, kingCurrCol + 1, gameBoard))
	{
		Piece *newKing = new King(king->isWhite, king->getType(), Pos{kingCurrRow, kingCurrCol + 1});
		if (newKing->inCheck(gameBoard))
		{
			// cannot move to position
			++checks;
		}
		delete newKing;
	}
	else
	{
		++checks;
	}

	if (king->validMove(kingCurrRow + 1, kingCurrCol, gameBoard))
	{
		Piece *newKing = new King(king->isWhite, king->getType(), Pos{kingCurrRow + 1, kingCurrCol});
		if (newKing->inCheck(gameBoard))
		{
			// cannot move to position
			++checks;
		}
		delete newKing;
	}
	else
	{
		++checks;
	}

	if (king->validMove(kingCurrRow - 1, kingCurrCol - 1, gameBoard))
	{
		Piece *newKing = new King(king->isWhite, king->getType(), Pos{kingCurrRow - 1, kingCurrCol - 1});
		if (newKing->inCheck(gameBoard))
		{
			// cannot move to position
			++checks;
		}
		delete newKing;
	}
	else
	{
		++checks;
	}

	if (king->validMove(kingCurrRow + 1, kingCurrCol - 1, gameBoard))
	{
		Piece *newKing = new King(king->isWhite, king->getType(), Pos{kingCurrRow + 1, kingCurrCol - 1});
		if (newKing->inCheck(gameBoard))
		{
			// cannot move to position
			++checks;
		}
		delete newKing;
	}
	else
	{
		++checks;
	}

	if (king->validMove(kingCurrRow - 1, kingCurrCol + 1, gameBoard))
	{
		Piece *newKing = new King(king->isWhite, king->getType(), Pos{kingCurrRow - 1, kingCurrCol + 1});
		if (newKing->inCheck(gameBoard))
		{
			// cannot move to position
			++checks;
		}
		delete newKing;
	}
	else
	{
		++checks;
	}

	if (king->validMove(kingCurrRow - 1, kingCurrCol, gameBoard))
	{
		Piece *newKing = new King(king->isWhite, king->getType(), Pos{kingCurrRow - 1, kingCurrCol});
		if (newKing->inCheck(gameBoard))
		{
			// cannot move to position
			++checks;
		}
		delete newKing;
	}
	else
	{
		++checks;
	}

	if (king->validMove(kingCurrRow, kingCurrCol - 1, gameBoard))
	{
		Piece *newKing = new King(king->isWhite, king->getType(), Pos{kingCurrRow, kingCurrCol - 1});
		if (newKing->inCheck(gameBoard))
		{
			// cannot move to position
			++checks;
		}
		delete newKing;
	}
	else
	{
		++checks;
	}
	// checks it there's any valid moves possibles depending on checks
	if (checks == 8)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// returns true if the move is a valid enpassant move
bool GameBoard::isEnpassantMove(int corStartRow, int corStartCol, int corEndRow, int corEndCol)
{
	Piece *p = gameBoard[corStartRow][corStartCol];
	// if the piece we are moving is white
	if (p->isWhite)
	{
		// moving left
		if (validCoord(corStartRow - 1) && validCoord(corStartCol - 1) && (corStartRow - 1 == corEndRow) && (corStartCol - 1 == corEndCol) && (gameBoard[corStartRow - 1][corStartCol - 1] == nullptr) &&
			(gameBoard[corStartRow][corStartCol - 1] != nullptr) &&
			(gameBoard[corStartRow][corStartCol - 1]->getType() == 'p'))
		{
			deletePiece(corStartRow, corStartCol - 1);
			enpassantLeft = true;
			return true;
		}
		// moving right
		else if (validCoord(corStartRow - 1) && validCoord(corStartCol + 1) && (corStartRow - 1 == corEndRow) && (corStartCol + 1 == corEndCol) && (gameBoard[corStartRow - 1][corStartCol + 1] == nullptr) &&
				 (gameBoard[corStartRow][corStartCol + 1] != nullptr) &&
				 (gameBoard[corStartRow][corStartCol + 1]->getType() == 'p'))
		{
			deletePiece(corStartRow, corStartCol + 1);
			enpassantRight = true;
			return true;
		}
	}
	// pawn we are moving is black
	else
	{
		// moving left
		if (validCoord(corStartRow + 1) && validCoord(corStartCol - 1) && (corStartRow + 1 == corEndRow) && (corStartCol - 1 == corEndCol) && (gameBoard[corStartRow + 1][corStartCol - 1] == nullptr) &&
			(gameBoard[corStartRow][corStartCol - 1] != nullptr) &&
			(gameBoard[corStartRow][corStartCol - 1]->getType() == 'P'))
		{
			deletePiece(corStartRow, corStartCol - 1);
			enpassantLeft = true;
			return true;
		}
		// moving right
		else if (validCoord(corStartRow + 1) && validCoord(corStartCol + 1) && (corStartRow + 1 == corEndRow) && (corStartCol + 1 == corEndCol) && (gameBoard[corStartRow + 1][corStartCol + 1] == nullptr) &&
				 (gameBoard[corStartRow][corStartCol + 1] != nullptr) &&
				 (gameBoard[corStartRow][corStartCol + 1]->getType() == 'P'))
		{
			deletePiece(corStartRow, corStartCol + 1);
			enpassantRight = true;
			return true;
		}
	}
	return false;
}

bool GameBoard::isDraw()
{
	// will check if there's a draw on the board
	int numOfPieces = 0;
	int numOfKings = 0;
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			Piece *p = gameBoard[i][j];
			if (p != nullptr)
			{
				++numOfPieces;
				if (p->getType() == 'K' || p->getType() == 'k')
				{
					++numOfKings;
				}
			}
		}
	}
	if (numOfPieces == 2 && numOfKings == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Piece *GameBoard::get(int row, int col) const
{
	return gameBoard[row][col];
}

void GameBoard::clearTheBoard()
{
	// initalize everything else as a nullptr
	for (int i = 0; i <= 7; i++)
	{
		// this is left to right -> columns
		for (int j = 0; j <= 7; j++)
		{
			// this is top to bottom -> rows
			gameBoard[j][i] = nullptr;
		}
	}
}

// moves the piece from the startRow & startCol to endRow & endCol if it's a valid move
void GameBoard::movePiece(int startRow, char startCol, int endRow, char endCol)
{
	int corStartRow = getCorrRow(startRow);
	int corStartCol = getCorrCol(startCol);
	int corEndRow = getCorrRow(endRow);
	int corEndCol = getCorrCol(endCol);
	// see if the coordinates we are moving the pieces are first valid!!
	if (!validCoord(corStartRow) || !validCoord(corStartCol) || !validCoord(corEndRow) || !validCoord(corEndCol))
	{
		cout << "Sorry that's invalid move as that move is not on the board!" << endl;
		return;
	}
	// gets the corresponding piece on the start square
	Piece *p = gameBoard[corStartRow][corStartCol];
	// sees if we can actually move that piece
	if (p != nullptr && ((isWhiteTurn() && p->isWhite) || (!isWhiteTurn() && !p->isWhite)))
	{
		if (p->validMove(corEndRow, corEndCol, gameBoard))
		{
			// checks to see if it's an enpassant move
			isEnpassantMove(corStartRow, corStartCol, corEndRow, corEndCol);
			// will update the board to move to that square
			placePiece(p->isWhite, p->getType(), corEndRow, corEndCol);
			deletePiece(corStartRow, corStartCol);
			// gets the king and sees if the move caused the king to be in check
			string kingPos = getKing(isWhiteMove);
			int kingPosRow = kingPos[0] - '0';
			int kingPosCol = kingPos[1] - '0';
			Piece *k = gameBoard[kingPosRow][kingPosCol];
			if (k->inCheck(gameBoard))
			{
				// king is in check, cannot move that piece. thus revert the board back
				deletePiece(corEndRow, corEndCol);
				placePiece(p->isWhite, p->getType(), corStartRow, corStartCol);
				gameBoard[corStartRow][corStartCol]->setPosition(corStartRow, corStartCol);
				cout << "Sorry invalid move as your king is in check!" << endl;
				return;
			}
			// continues here if the king is not in check
			// checks to see if the move caused the opposing king to be in check
			string oppKingPos = getKing(!isWhiteMove);
			int oppKingPosRow = oppKingPos[0] - '0';
			int oppKingPosCol = oppKingPos[1] - '0';
			Piece *oppKing = gameBoard[oppKingPosRow][oppKingPosCol];
			if (oppKing->inCheck(gameBoard))
			{
				// checks to see if the move caused a checkmate
				if (inCheckmate(!isWhiteMove))
				{
					endGame = true;
					// will reset the board in main
					return;
				}
				// means the opposing king is in check
				currentlyInCheck = true;
			}
			// checks to see if the move caused a draw
			if (isDraw())
			{
				currentlyDraw = true;
				return;
			}
			// handles the case for castling. sees if the piece we are moving is a king
			// if we are castling the white king
			if (p->getType() == 'K')
			{
				// queen side castline (left)
				if (corStartRow == 7 && corStartCol == 4 && corEndRow == 7 && corEndCol == 2)
				{
					Piece *rook = gameBoard[7][0];
					gameBoard[7][3] = rook;
					gameBoard[7][0] = nullptr;
					rook->setPosition(7, 3);
					castleLeft = true;
				}
				// king side castling (right)
				else if (corStartRow == 7 && corStartCol == 4 && corEndRow == 7 && corEndCol == 6)
				{
					Piece *rook = gameBoard[7][7];
					gameBoard[7][5] = rook;
					gameBoard[7][7] = nullptr;
					rook->setPosition(7, 5);
					castleRight = true;
				}
			}
			// moving black king
			else if (p->getType() == 'k')
			{
				// queen side castline == left
				if (corStartRow == 0 && corStartCol == 4 && corEndRow == 0 && corEndCol == 2)
				{
					Piece *rook = gameBoard[0][0];
					gameBoard[0][3] = rook;
					gameBoard[0][0] = nullptr;
					rook->setPosition(0, 3);
					castleLeft = true;
				}
				// king side castling (right)
				else if (corStartRow == 0 && corStartCol == 4 && corEndRow == 0 && corEndCol == 6)
				{
					Piece *rook = gameBoard[0][7];
					gameBoard[0][5] = rook;
					gameBoard[0][7] = nullptr;
					rook->setPosition(0, 5);
					castleRight = true;
				}
			}
			// Pawn promotion case
			// promoting a white pawn
			if (p->getType() == 'P')
			{
				if (corEndRow == 0)
				{
					char piece;
					cin >> piece;
					// updates the board to the new piece
					if (piece == 'R' || piece == 'N' || piece == 'B' || piece == 'Q')
					{
						placePiece(true, piece, corEndRow, corEndCol);
					}
					else
					{
						cout << "Invalid piece for pawn promotion" << endl;
						deletePiece(corEndRow, corEndCol);
						placePiece(p->isWhite, p->getType(), corStartRow, corStartCol);
						return;
					}
				}
			}
			// promoting a black pawn
			else if (p->getType() == 'p')
			{
				if (corEndRow == 7)
				{
					char piece;
					cin >> piece;
					// updates the board to the new piece
					if (piece == 'r' || piece == 'n' || piece == 'b' || piece == 'q')
					{
						// they input it right
						placePiece(false, piece, corEndRow, corEndCol);
					}
					else
					{
						cout << "Invalid piece for pawn promotion" << endl;
						deletePiece(corEndRow, corEndCol);
						placePiece(p->isWhite, p->getType(), corStartRow, corStartCol);
						isWhiteMove = false;
						return;
					}
				}
			}
			// will make it the other player's turn
			isWhiteMove = !isWhiteMove;
		}
		else
		{
			cout << "Sorry invalid move!!" << endl;
		}
	}
	else
	{
		cout << "Cannot move piece!!" << endl;
	}
}

// will check if it's valid based on number of black and white kings and if a pawn not on back end
bool GameBoard::boardValid()
{
	int blackKings = 0;
	int whiteKings = 0;

	// check to see if pawns are on the end files
	for (int row = 0; row <= 7; row++)
	{
		for (int col = 0; col <= 7; col++)
		{
			Piece *p = gameBoard[row][col];
			if (p)
			{
				if ((p->getType() == 'P' || p->getType() == 'p') && (row == 0 || row == 7))
					return false;
				else if (p->getType() == 'K')
					++whiteKings;
				else if (p->getType() == 'k')
					++blackKings;
			}
		}
	}
	if (blackKings == 1 && whiteKings == 1)
		return true;
	else
		return false;
}

GameBoard::~GameBoard()
{
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			delete gameBoard[i][j];
			gameBoard[i][j] = nullptr;
		}
	}
}

void GameBoard::defaultSetup()
{
	// setups the board to a default setup
	// setup the white pieces:
	gameBoard[7][0] = new Rook(true, 'R', Pos{7, 0});
	gameBoard[7][1] = new Knight(true, 'N', Pos{7, 1});
	gameBoard[7][2] = new Bishop(true, 'B', Pos{7, 2});
	gameBoard[7][3] = new Queen(true, 'Q', Pos{7, 3});
	gameBoard[7][4] = new King(true, 'K', Pos{7, 4});
	gameBoard[7][5] = new Bishop(true, 'B', Pos{7, 5});
	gameBoard[7][6] = new Knight(true, 'N', Pos{7, 6});
	gameBoard[7][7] = new Rook(true, 'R', Pos{7, 7});

	// setup the black pieces:
	gameBoard[0][0] = new Rook(false, 'r', Pos{0, 0});
	gameBoard[0][1] = new Knight(false, 'n', Pos{0, 1});
	gameBoard[0][2] = new Bishop(false, 'b', Pos{0, 2});
	gameBoard[0][3] = new Queen(false, 'q', Pos{0, 3});
	gameBoard[0][4] = new King(false, 'k', Pos{0, 4});
	gameBoard[0][5] = new Bishop(false, 'b', Pos{0, 5});
	gameBoard[0][6] = new Knight(false, 'n', Pos{0, 6});
	gameBoard[0][7] = new Rook(false, 'r', Pos{0, 7});

	// setup the pawns:
	for (int i = 0; i <= 7; i++)
	{
		// white pawns
		gameBoard[1][i] = new Pawn(false, 'p', Pos{1, i});
		// black pawns
		gameBoard[6][i] = new Pawn(true, 'P', Pos{6, i});
	}

	// initalize everything else as a nullptr
	for (int i = 0; i <= 7; i++)
	{
		// this is left to right -> columns
		for (int j = 2; j <= 5; j++)
		{
			// this is top to bottom -> rows
			gameBoard[j][i] = nullptr;
		}
	}
}

void GameBoard::resetGame()
{
	setupBoard = false;
	endGame = false;
	isWhiteMove = true;
	clearTheBoard();
	setupBoard = false;
	currentlyInCheck = false;
	currentlyDraw = false;
	castleLeft = false;
	castleRight = false;
	enpassantLeft = false;
	enpassantRight = false;
}

GameBoard::GameBoard()
{
	setupBoard = false;
	endGame = false;
	display = new TextDisplay();
	display->setBoard(*this);
	whitePlayer = new Player(true);
	whitePlayer->setBoard(*this);
	blackPlayer = new Player(false);
	blackPlayer->setBoard(*this);
	isWhiteMove = true;
	currentlyInCheck = false;
	currentlyDraw = false;
	castleLeft = false;
	castleRight = false;
	enpassantLeft = false;
	enpassantRight = false;
	clearTheBoard();
}

std::ostream &operator<<(std::ostream &out, const GameBoard &b)
{
	// will output the gameboard using the textdisplay
	out << *(b.display);
	return out;
}
