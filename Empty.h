#ifndef __EMPTY_H__
#define __EMPTY_H__
#include <string>
#include <iostream>
#include "Piece.h"
using namespace std;

class Empty : public Piece {
	private:
	  bool moved;
	  string colour = "empty";

	public:
	  Empty(bool isW, char t, Pos p);
	  ~Empty();
	  bool check();
};

#endif
