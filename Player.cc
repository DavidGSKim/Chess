#include "Player.h"
#include <string>
#include <iostream>

Player::Player(bool isWhite) : white(isWhite)
{
}

// sets the player object pointing to the board
void Player::setBoard(GameBoard &game)
{
    g = &game;
}

// sets the player to see if it's a human player or a computer player
void Player::setHuman(string isHuman)
{
    if (isHuman == "human")
    {
        human = true;
    }
    else if (isHuman == "computer")
    {
        human = false;
    }
    else
    {
        cout << "Sorry invalid command" << endl;
    }
}

Player::~Player() {}

// moves the piece, depending on if the player is a human or computer
void Player::move(string curPos, string dest)
{
    if (human)
    {
        // means the player is human

        int theCol = g->getCorrCol(curPos[0]);
        int theRow = g->getCorrRow(curPos[1]);

        Piece *thePiece = g->gameBoard[theRow][theCol];
        if (thePiece != nullptr)
        {
            // means it can move the piece
        }
    }
    else
    {
        // means its a computer player's move
    }
}
