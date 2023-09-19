#include <iostream>
#include "scoreboard.h"
using namespace std;

void Scoreboard::Start() {} 

void Scoreboard::End(string winner)
{
    if (winner == "white") { // if white wins increment 1
        white++;
    } else if (winner == "black") { // if black wins increment 1
        black++;
    } else { // if neither conditions are met it must be a draw so increment 0.5 for both
        white += 0.5;
        black += 0.5;
    }
}

void Scoreboard::PrintScore()
{
    cout << "Final Score:" << endl;
    cout << "White:" << white << endl;
    cout << "Black:" << black << endl;
}

Scoreboard::Scoreboard()
{
    white = 0;
    black = 0;
}
