#include "graphicsdisplay.h"
#include "GameBoard.h"
#include <sstream>
#include "Piece.h"

GraphicsDisplay::GraphicsDisplay(int n) : b(nullptr), size(n), Xoffset(-size / 40), Yoffset(size / 40), w1(Xwindow(size, size)){};

// sets the graphics display board to point at the gameboard
void GraphicsDisplay::initBoard(GameBoard *b)
{
	this->b = b;
}

// updates the graphics display depending on what the move is
void GraphicsDisplay::update(Xwindow &disp, int sRow, int sCol, int eRow, int eCol)
{
	int textColour = Xwindow::Black;
	int squareSize = size / 10;
	int squareColour = Xwindow::Red;
	// checks to see if the move coordinates are within the bounds of the board
	if (0 <= eRow && eRow <= 7 && 0 <= eCol && eCol <= 7)
	{
		// outputs the colour square
		if ((sRow + sCol) % 2 == 1)
		{
			squareColour = Xwindow::DarkGreen;
		}
		disp.fillRectangle(squareSize * (sCol + 1), squareSize * (sRow + 1), squareSize, squareSize, squareColour);
		squareColour = Xwindow::Red;
		if ((eRow + eCol) % 2 == 1)
		{
			squareColour = Xwindow::DarkGreen;
		}
		disp.fillRectangle(squareSize * (eCol + 1), squareSize * (eRow + 1), squareSize, squareSize, squareColour);
		// if a piece exists on the end move, output the text of the piece
		if (b->get(eRow, eCol) != nullptr)
		{
			stringstream ss;
			ss << b->get(eRow, eCol)->getType();
			if (b->get(eRow, eCol)->isWhite)
			{
				textColour = Xwindow::White;
			}
			disp.drawBigString(squareSize * (eCol + 1.5) + Xoffset, (eRow + 1.5) * squareSize + Yoffset, ss.str(), textColour);
		}
		// if there is a piece on the starting square, output it
		if (b->get(sRow, sCol) != nullptr)
		{
			stringstream ss;
			ss << b->get(sRow, sCol)->getType();
			if (b->get(sRow, sCol)->isWhite)
			{
				textColour = Xwindow::White;
			}
			disp.drawBigString(squareSize * (sCol + 1.5) + Xoffset, (sRow + 1.5) * squareSize + Yoffset, ss.str(), textColour);
		}
	}
}

// will draw the iinital board
void GraphicsDisplay::drawBoard(Xwindow &disp)
{
	int squareSize = size / 10;
	int squareColour = Xwindow::Red;
	int textColour = Xwindow::Black;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			disp.fillRectangle(squareSize * j, squareSize * i, squareSize, squareSize, squareColour);
			if (squareColour == Xwindow::Red && j != 8)
			{
				squareColour = Xwindow::DarkGreen;
			}
			else if (j != 8)
			{
				squareColour = Xwindow::Red;
			}
		}
	}
	// outputs the rank and file
	for (int i = 1; i < 9; i++)
	{
		char cRank = 8 - i + '0' + 1;
		char cFile = 'A' + i - 1;
		std::string sRank;
		std::string sFile;
		std::stringstream ssRank;
		std::stringstream ssFile;
		ssRank << cRank;
		ssFile << cFile;
		ssRank >> sRank;
		ssFile >> sFile;
		disp.drawBigString(squareSize / 3, squareSize * i + squareSize / 1.5, sRank, textColour);
		disp.drawBigString(squareSize * i + squareSize / 3, squareSize / 1.5, sFile, textColour);
		disp.drawBigString(28 * squareSize / 3, squareSize * i + squareSize / 1.5, sRank, textColour);
		disp.drawBigString(squareSize * i + squareSize / 3, 14.5 * squareSize / 1.5, sFile, textColour);
	}
	// outputs the pieces initally
	for (int row = 0; row <= 7; row++)
	{
		for (int col = 0; col <= 7; col++)
		{
			if (b->get(row, col))
			{
				stringstream ss;
				ss << b->get(row, col)->getType();
				if (b->get(row, col)->isWhite)
				{
					disp.drawBigString(squareSize * (col + 1.5) + Xoffset, (row + 1.5) * (squareSize) + Yoffset, ss.str(), Xwindow::White);
				}
				else
				{
					disp.drawBigString(squareSize * (col + 1.5) + Xoffset, (row + 1.5) * (squareSize) + Yoffset, ss.str(), Xwindow::Black);
				}
			}
		}
	}
}
