#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__
#include <string>

class Scoreboard
{
    float white;
    float black;

public:
    void Start();                 // starts a game
    void End(std::string winner); // ends the game as well as incrementing the score of winner
    void PrintScore();            // prints the score
    Scoreboard();
};

#endif