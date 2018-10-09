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
    std::queue<Chess> generateNextStep();
    int evaluateSituation(int role);
    bool hasNeighbor(QPoint pos, int distance, int count);
    int scorePoint(QPoint pos, int role);
    int countToScore(int count, int block, int empty);
};

enum Score
{
    ONE = 10,
    TWO = 100,
    THREE = 1000,
    FOUR = 100000,
    FIVE = 10000000,
    BLOCKED_ONE = 1,
    BLOCKED_TWO = 10,
    BLOCKED_THREE = 100,
    BLOCKED_FOUR = 10000
}
#endif // CHESSBOARD_H
