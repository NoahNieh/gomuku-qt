#ifndef AI_H
#define AI_H
#include "player.h"
#include <QObject>
#include <QWidget>
#include <limits.h>
struct grade
{
     int score;
     QPoint pos;
};


class Ai : public Player
{
public:
    Ai();
    Ai(int role);
    QPoint generateNextStep(Chessboard chessboard,int difficulty, int role);
    grade min_alphabeta(Chessboard chessboard, int depth, int alpha, int beta, int role, bool considerDeep);
    grade max_alphabeta(Chessboard chessboard, int depth, int alpha, int beta, int role, bool considerDeep, bool firstStep);
    grade iterative_deepening(Chessboard chessboard,int depth, int role);
};


#endif // AI_H
