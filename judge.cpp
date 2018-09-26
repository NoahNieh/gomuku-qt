#include "judge.h"

Judge::Judge()
{
    chessboard = new Chessboard;
    term = 1;
    game_mode = 2;
}

int Judge::getTerm()
{
    return this->term;
}

Player Judge::getPlayer(int n)
{
    return *(this->player[n]);
}

int Judge::getGameMode()
{
    return this->game_mode;
}

Chessboard* Judge::getChessboard()
{
    return this->chessboard;
}

int Judge::putChess(QPoint pos)
{

    if(chessboard->getChess(pos) != 0)
    {
        return -1;
    }

    chessboard->setChess(pos, term);
    if(term == 1)
    {
        term = 2;
    }
    else if(term == 2)
    {
        term = 1;
    }
    return 0;
}

Judge::~Judge()
{
    delete[] chessboard;
}
