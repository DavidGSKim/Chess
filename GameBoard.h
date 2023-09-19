#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__
#include <string>

class Piece;
class TextDisplay;
class Player;
using namespace std;
class GameBoard
{
public:
	bool isWhiteMove;

	bool endGame;
	bool setupBoard;
	bool currentlyInCheck;
	bool currentlyDraw;
	bool castleLeft;
	bool castleRight;
	bool enpassantLeft;
	bool enpassantRight;
	bool isWhiteTurn();
	Player *whitePlayer;
	Player *blackPlayer;
	Piece *gameBoard[8][8];
	TextDisplay *display;
	GameBoard();
	virtual ~GameBoard();
	void placePiece(bool isWhite, char piece, int row, int col);
	Piece *get(int row, int col) const;
	void deletePiece(int row, int col);
	string getKing(bool isWhite);
	void clearTheBoard();
	void resetGame();
	void movePiece(int startRow, char startCol, int endRow, char endCol);
	bool validCoord(int num);
	bool boardValid();
	void defaultSetup();
	bool isDraw();
	int getCorrRow(int c);
	int getCorrCol(char c);
	bool inCheckmate(bool isWhite);
	bool isEnpassantMove(int corStartRow, int corStartCol, int corEndRow, int corEndCol);
	friend std::ostream &operator<<(std::ostream &out, const GameBoard &b);
};

#endif