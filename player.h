#ifndef PLAYER_H
#define PLAYER_H

#include "chessboard.h"


class Player
{
private:
    int side;
    int time;
    int win;
public:
    Player();

//    virtual int put(Chessboard chessboard) = 0;
};

#endif // PLAYER_H
