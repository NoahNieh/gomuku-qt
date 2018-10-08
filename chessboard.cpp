#include "chessboard.h"

Chessboard::Chessboard()
{
    for(int i = 0; i<15; i++)
    {
        for(int j = 0; j<15; j++)
        {
            this->chessboard[i][j] = 0;
        }
    }
}

int Chessboard::setChess(QPoint pos, int role)
{
    chessboard[pos.x()][pos.y()] = role;
    return 0;
}



int Chessboard::getChess(QPoint pos)
{
    if(pos.x()>=15 || pos.x()<0 || pos.y()<0 || pos.y()>=15) return 0;
    return this->chessboard[pos.x()][pos.y()];
}
