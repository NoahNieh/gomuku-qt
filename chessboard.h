#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QWidget>
#include <queue>

class Chessboard
{
private:
    int chessboard[15][15];
public:
    Chessboard();
    int setChess(QPoint pos, int role);
    int getChess(QPoint pos);
//    int isWin(Chess c);
//    int evaluateSituation(int side);
//    std::queue<Chess> generateNextStep();
};

#endif // CHESSBOARD_H
