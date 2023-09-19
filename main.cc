#include <string>
#include <iostream>
#include <sstream>
// include all the classes
#include "GameBoard.h"
#include "TextDisplay.h"
#include "Piece.h"
#include "Player.h"
#include "scoreboard.h"
#include "graphicsdisplay.h"
using namespace std;

bool isWhite(char piece)
{
    if (piece >= 'A' && piece <= 'Z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    // calls the GamebBoard, ScoreBoard, and GraphicsDisplay objects
    GameBoard *board = new GameBoard();
    Scoreboard *score = new Scoreboard();
    GraphicsDisplay graphics(500);
    // command stores in the user input
    string command;
    while (cin >> command)
    {
        if (command == "game")
        {
            if (!board->setupBoard)
            {
                board->defaultSetup();
                // setup the graphics display
                graphics.initBoard(board);
                graphics.drawBoard(graphics.w1);
            }
            string firstPlayer;
            string secondPlayer;
            cin >> firstPlayer >> secondPlayer;
            // sets up the player objects
            board->whitePlayer->setHuman(firstPlayer);
            board->blackPlayer->setHuman(secondPlayer);
            cout << *board << endl;
            if (board->isDraw())
            {
                cout << "It's a draw!" << endl;
                score->End("draw");
                board->resetGame();
            }
            else
            {
                board->setupBoard = true;
                if (board->isWhiteMove)
                {
                    cout << "White to move" << endl;
                }
                else
                {
                    cout << "Black to move" << endl;
                }
            }
        }
        else if (command == "resign")
        {
            if (board->isWhiteTurn())
            {
                // means black won
                cout << " White resigns. Black wins!!" << endl;
                // update scoreboard
                score->End("black");
            }
            else
            {
                // white won
                cout << " Black resigns. White wins!!" << endl;
                // update scoreboard
                score->End("white");
            }

            // clears the board and resets the game
            board->resetGame();
        }
        else if (command == "move")
        {
            if (board->setupBoard)
            {
                int sRow;
                char sCol;
                int eRow;
                char eCol;
                cin >> sCol >> sRow >> eCol >> eRow;
                // will attempt to move the piece on the board
                board->movePiece(sRow, sCol, eRow, eCol);
                int newSRow = board->getCorrRow(sRow);
                int newSCol = board->getCorrCol(sCol);
                int newERow = board->getCorrRow(eRow);
                int newECol = board->getCorrCol(eCol);
                // update the graphics using the piece you move it from and to
                graphics.update(graphics.w1, newSRow, newSCol, newERow, newECol);
                if (board->castleLeft)
                {
                    graphics.update(graphics.w1, newSRow, 0, newERow, 3);
                    board->castleLeft = false;
                }
                else if (board->castleRight)
                {
                    graphics.update(graphics.w1, newSRow, 7, newERow, 5);
                    board->castleRight = false;
                }
                if (board->enpassantRight)
                {
                    graphics.update(graphics.w1, newSRow, newSCol + 1, newSRow, newSCol + 1);
                    board->enpassantRight = false;
                }
                else if (board->enpassantLeft)
                {
                    graphics.update(graphics.w1, newSRow, newSCol - 1, newSRow, newSCol - 1);
                    board->enpassantLeft = false;
                }
                cout << *board << endl;
                // checks to see if the board is in checkmate
                if (board->endGame)
                {
                    if (board->isWhiteMove)
                    {
                        cout << "Checkmate! White won" << endl;
                        score->End("white");
                    }
                    else
                    {
                        cout << " Checkmate! Black won" << endl;
                        score->End("black");
                    }
                    board->resetGame();
                }
                // checks if board is in a draw
                else if (board->isDraw())
                {
                    cout << "It's a draw!" << endl;
                    score->End("draw");
                    board->resetGame();
                }
                else
                {
                    // if a king is currently in check
                    if (board->currentlyInCheck)
                    {
                        if (board->isWhiteMove)
                        {
                            cout << "White is in check" << endl;
                        }
                        else
                        {
                            cout << "Black is in check" << endl;
                        }

                        board->currentlyInCheck = false;
                    }
                    // say who's turn it is
                    if (board->isWhiteMove)
                    {
                        cout << "White to move" << endl;
                    }
                    else
                    {
                        cout << "Black to move" << endl;
                    }
                }
            }
            else
            {
                cout << "Setup the board with please!" << endl;
            }
        }
        else if (command == "setup")
        {
            // start with a new gameboard
            delete board;
            board = new GameBoard();
            // setup graphics display
            graphics.initBoard(board);
            graphics.drawBoard(graphics.w1);
            string action;
            while (cin >> action)
            {
                if (action == "+")
                {
                    // adds a piece
                    char piece;
                    char col;
                    int row;
                    cin >> piece >> col >> row;
                    int theCol = board->getCorrCol(col);
                    int theRow = board->getCorrRow(row);
                    bool white = isWhite(piece);
                    board->placePiece(white, piece, theRow, theCol);
                    cout << *board << endl;
                    graphics.update(graphics.w1, theRow, theCol, theRow, theCol);
                }
                else if (action == "-")
                {
                    // removes a piece
                    char col;
                    int row;
                    cin >> col >> row;
                    int theCol = board->getCorrCol(col);
                    int theRow = board->getCorrRow(row);
                    board->deletePiece(theRow, theCol);
                    cout << *board << endl;
                    graphics.update(graphics.w1, theRow, theCol, theRow, theCol);
                }
                else if (action == "=")
                {
                    // will set who's turn it is
                    string colour;
                    cin >> colour;
                    if (colour == "white")
                    {
                        board->isWhiteMove = true;
                    }
                    else if (colour == "black")
                    {
                        board->isWhiteMove = false;
                    }
                }
                else if (action == "done")
                {
                    // checks to see if board is valid, and then exits setup
                    if (board->boardValid())
                    {
                        board->setupBoard = true;
                        cout << "Successfully exited setup" << endl;
                        break;
                    }
                    else
                    {
                        cout << "Error, cannot leave setup mode. Invalid Board" << endl;
                    }
                }
                else
                {
                    cin.ignore();
                    cin.clear();
                    cout << "Sorry error message" << endl;
                }
            }
        }
        else
        {
            cin.ignore();
            cin.clear();
            cout << "Sorry, invalid error command" << endl;
        }
    }
    // prints the final scoreboard
    score->PrintScore();
    delete board;
}