#ifndef JUDGE_H
#define JUDGE_H

#include <QObject>
#include <QWidget>
#include "chessboard.h"
#include "player.h"

class Judge
{
private:
    Chessboard *chessboard;
    Player *player[2];
    int term;
    int winner;
    int game_mode; // 0, 1:ai, 2:hum
public:
    Judge();
    int getTerm();
    Player* getPlayer(int n);
    int getGameMode();
    Chessboard* getChessboard();
    int putChess(QPoint pos);
    QPoint putChessAi();
    int playWithCom(int go_first);
    int playWithHum();
    int resetJudge(); //tmp
    int isWin(QPoint pos);
    ~Judge();
    int getWinner() const;
    void setWinner(int winner);
};

#endif // JUDGE_H
