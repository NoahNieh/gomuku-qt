#include "judge.h"
#include "ai.h"
#include "human.h"
#include <QDebug>

int Judge::getWinner() const
{
    return winner;
}

void Judge::setWinner(int value)
{
    winner = value;
}

Judge::Judge()
{
    this->chessboard = NULL;
    this->term = 0;
    this->winner = 0;
    this->game_mode = 0;
    this->player[0] = NULL;
    this->player[1] = NULL;
}

int Judge::getTerm()
{
    return this->term;
}

Player* Judge::getPlayer(int n)
{
    return this->player[n];
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
    if(isWin(pos)) return 1;
    this->term = this->term == 1 ? 2 : 1;

    return 0;
}

QPoint Judge::putChessAi()
{
    return this->player[this->term-1]->generateNextStep(*(this->chessboard), 10, this->term);
}

int Judge::playWithCom(int go_first)
{
    if(go_first == 1)
    {
        player[0] = new Human(1);
        player[1] = new Ai(2);
    }
    else
    {
        player[0] = new Ai(1);
        player[1] = new Human(2);
    }
    if(chessboard != NULL)
    {
        delete chessboard;
    }
    this->chessboard = new Chessboard();
    this->game_mode = 1;
    this->term = 1;
    if(go_first == 2)
    {
        this->chessboard->setChess(QPoint(7, 7), 1);
        this->term = 2;
    }
    this->winner = 0;
    return 0;
}



int Judge::playWithHum()
{
    player[0] = new Human();
    player[1] = new Human();
    if(chessboard != NULL)
    {
        delete chessboard;
    }
    chessboard = new Chessboard();
    game_mode = 2;
    term = 1;
    this->winner = 0;
    return 0;
}

int Judge::resetJudge()
{
    term = 0;
    game_mode = 0;
    return 0;
}

int Judge::isWin(QPoint pos)
{

    int sumOfChess;
    int direction[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    int minus;
    for(int i = 0; i<4; i++)
    {
        minus = 1;
        if(sumOfChess == 5) break;
        sumOfChess = 1;
        QPoint checker = pos;
//        qDebug() << "r" << i;
        for(int j = 0; j<5; j++)
        {
            checker.setX(checker.x()+direction[i][0] * minus);
            checker.setY(checker.y()+direction[i][1] * minus);
            if(chessboard->getChess(checker) == term)
            {
                sumOfChess++;
//                qDebug() << checker.x() << ", " << checker.y();
            }
            else
            {
                if(minus == -1) break;
                else
                {
                    minus = -1, j = 0;
                    checker = pos;
                }
            }
        }
    }
    if(sumOfChess == 5)
    {
        this->winner = this->term;
        return 1;
    }
    else return 0;
}

Judge::~Judge()
{
    delete chessboard;
    delete player[0];
    delete player[1];

}
