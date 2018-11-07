#include "newjudge.h"
#include "newhuman.h"
#include "stack"
#include "chessboard.h"
#include <QObject>
#include <QWidget>

Newjudge :: Newjudge()
{
    chessboard = NULL;
    term = 0;
    game_mode = 0;//感觉这个初始有些问题
    player[0] = NULL;
    player[1] = NULL;

}

int Newjudge::playInNewRule()
{
    player[0] = new Newhuman();
    player[1] = new Newhuman();
    if(chessboard != NULL)
    {
        delete chessboard;
    }
    chessboard = new Chessboard();
    game_mode = 3;//这个模式怕是有些问题
    term = 1;
    return 0;
}

//每下一步减少一个棋子
int Newjudge::dechessnum(Newhuman player)
{
    player.setChessnum(-1);
    return 0;
}

QPoint *Newjudge::theFivePoint(QPoint pos)
{

    QPoint pointLine[5];
    pointLine[4] = pos;
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
                this->points.push(checker);
                //有些问题
//                qDebug() << checker.x() << ", " << checker.y();
            }
            else
            {
               /* if(minus == -1) break;
                else
                {
                    minus = -1, j = 0;
                    checker = pos;
                }*/
                while(!points.empty())
                    points.pop();

            }
        }
    }
    for(int i=0;i<4;i++)
    {
        pointLine[i] = points.top();
    }
    if(sumOfChess == 5) return pointLine;
    else return NULL;

}


int Newjudge::clear(Newhuman player,QPoint pos[])
{
    for(int i=0;i<5;i++)
    {
        pos[i] = QPoint(0,0);
    }
    player.setChessnum(5) ;
    return 0;
}

int Newjudge::eat(Newhuman player,QPoint pos)
{
    //鼠标触发的棋子转化哦，怎么整
    player.setScore(1);
    player.setChessnum(-1);
    return 0;
}

int Newjudge::newWin(Newhuman player)//每次eat了以后就判断一下吧
{
    if(player.getScore() == 10)
    {
        printf("You win");
        return 0;
    }
}
