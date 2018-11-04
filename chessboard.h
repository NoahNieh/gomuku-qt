#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QWidget>
#include <queue>
#include <vector>
#include <map>
#include <stack>

class Chessboard
{
private:
    int chessboard[15][15];
    std::stack<QPoint> history;
public:
    Chessboard();
    ~Chessboard();
    int setChess(QPoint pos, int role);
    int getChess(QPoint pos);
    std::stack<QPoint> getHistory();
    std::vector<std::pair<QPoint, int> > generateNextStep(int role, bool considerCheckmate);
    int evaluateSituation(int role);
    bool hasNeighbor(QPoint pos, int distance, int count);
    int scorePoint(QPoint pos, int role);
    bool isPointOverThree(QPoint pos, int role);
    bool isScoreOverThree(int count, int block, int empty);
    int countToScore(int count, int block, int empty);
    static int compare(std::pair<QPoint, int> pair1, std::pair<QPoint, int> pair2);

};

enum Score
{
    ONE = 10,
    TWO = 100,
    THREE = 1000,
    FOUR = 1000000,
    FIVE = 100000000,
    BLOCKED_ONE = 1,
    BLOCKED_TWO = 10,
    BLOCKED_THREE = 100,
    BLOCKED_FOUR = 100000
};
#endif // CHESSBOARD_H
