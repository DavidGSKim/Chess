#include "Piece.h"
#include "GameBoard.h"
#include <iostream>
#include <string>
#include <sstream>

Piece::Piece(Pos &po, bool isW, char t) : position(po), isWhite(isW), type(t), enpassant(false) {}

Piece::~Piece() {}

char Piece::getType() const
{
    return type;
}

bool Piece::getIsWhite() const
{
    return isWhite;
}

void Piece::setPosition(int row, int col)
{
    this->position.row = row;
    this->position.column = col;
}

void Piece::setPieces(Piece *allPieces) {}