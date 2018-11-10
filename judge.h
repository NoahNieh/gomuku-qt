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
    int game_mode; // 0, 1:ai, 2:hum, 3:wait for connect
    bool is_your_term;
    int role;
public:
    Judge();
    int getTerm();
    Player* getPlayer(int n);
    int getGameMode();
    Chessboard* getChessboard();
    int putChess(QPoint pos);
    QPoint putChessAi();
    int playWithCom(int go_first);
    int playWithHum(int role);
    int resetJudge(); //tmp
    int isWin(QPoint pos);
    ~Judge();
    int getWinner() const;
    void setWinner(int winner);
    bool isYourTerm() const;
    void setGameMode(int value);
    int getRole() const;
    void setRole(int value);
    void restartGame();
signals:
    void restartGameSignal();
};

#endif // JUDGE_H
