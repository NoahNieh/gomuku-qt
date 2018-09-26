#ifndef AI_H
#define AI_H
#include "player.h"
#include <QObject>
#include <QWidget>

class Ai : public Player
{
public:
    Ai();
    QPoint generateNextStep(Chessboard chessboard);
};

#endif // AI_H
