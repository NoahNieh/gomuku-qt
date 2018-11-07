#ifndef NEWJUDGE_H
#define NEWJUDGE_H

#include "judge.h"
#include "player.h"
#include "chessboard.h"
#include "stack"
#include "newhuman.h"
#include <QObject>
#include <QWidget>

class Newjudge : public Judge
{
private:
    int game_mode; //0 无 1 进行
    Chessboard *chessboard;
    Player *player[2];
    int term;
    std::stack<QPoint> points;

public:
    Newjudge();
    int clear(Newhuman player,QPoint pos[]);
    int eat(Newhuman player,QPoint pos);
    int playInNewRule();
    int dechessnum(Newhuman player);
    int newWin(Newhuman player);
    QPoint *theFivePoint(QPoint pos);
    ~Newjudge();
};


#endif // NEWJUDGE_H
