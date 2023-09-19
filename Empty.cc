#include <iostream>
#include "Empty.h"
#include "Player.h"

Empty::Empty(bool isW, char t, Pos p) : Piece{p, isW, t} {}

Empty::~Empty() {}

bool Empty::check()
{
	return true;
}
