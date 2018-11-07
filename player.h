#ifndef PLAYER_H
#define PLAYER_H

#include "chessboard.h"


class Player
{
protected:
    int role;
    int time;
    int win;
public:
    Player();
    virtual ~Player();

    virtual QPoint generateNextStep(Chessboard chessboard,int difficulty, int role);
};

#endif // PLAYER_H
