#include "newhuman.h"

Newhuman :: Newhuman()
{
    this->score = 0;
    this->chessnum = 20;
    this->time = 0;
    this->win = 0;
}

int Newhuman::getScore()
{
    return this->score;
}

int Newhuman::getChessnum()
{
    return this->chessnum;
}

void Newhuman::setScore(int changeScore)
{
    this->score+=changeScore;
}

void Newhuman::setChessnum(int changeChessnum)
{
    this->chessnum+=changeChessnum;
}
