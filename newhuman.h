#ifndef NEWHUMAN_H
#define NEWHUMAN_H
#include "player.h"

class Newhuman : public Player
{
private:
    int score;
    int chessnum;
public:
    Newhuman();
    int getScore();
    void setScore(int changeScore);
    int getChessnum();
    void setChessnum(int changeChessnum);
};


#endif // NEWHUMAN_H
