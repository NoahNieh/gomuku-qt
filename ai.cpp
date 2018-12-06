#include "ai.h"
#include <QDebug>

Ai::Ai()
{
}

Ai::Ai(int role)
{
    this->role = role;
}




QPoint Ai::generateNextStep(Chessboard chessboard,int difficulty, int role)
{
    int deep = 2 * difficulty;
    grade best = iterative_deepening(chessboard, deep, role);
    return best.pos;
}

grade Ai::min_alphabeta(Chessboard chessboard, int depth, int alpha, int beta, int role)
{
    grade best;
    best.score = INT_MAX;
    std::vector<std::pair<QPoint, int> > nextstep = chessboard.generateNextStep(role, false);
    for(std::vector<std::pair<QPoint, int> >::iterator iter = nextstep.begin(); iter != nextstep.end(); iter++)
    {
        chessboard.setChess(iter->first, role);
        grade tmp = max_alphabeta(chessboard, depth-1, alpha, beta, role == 1 ? 2:1, false);
        chessboard.setChess(iter->first, 0);
        if (tmp.score < best.score)
        {
            best = tmp;
            alpha = tmp.score;
        }
        if (tmp.score < beta)
        {
            break;
        }
    }
    return best;
}


grade Ai::max_alphabeta(Chessboard chessboard, int depth, int alpha, int beta, int role, bool firstStep)
{
    grade best;
    grade tmp;
    best.score = INT_MIN;
    if(depth <= 0)
    {
        int res = chessboard.evaluateSituation(role);
        best.score = res;
        return best;
    }
    std::vector<std::pair<QPoint, int> > nextstep = chessboard.generateNextStep(role, false);
    for(std::vector<std::pair<QPoint, int> >::iterator iter = nextstep.begin(); iter != nextstep.end(); iter++)
    {
        chessboard.setChess(iter->first, role);
        tmp = min_alphabeta(chessboard, depth-1, alpha, beta, role == 1 ? 2:1);
        chessboard.setChess(iter->first, 0);

        if (tmp.score > best.score)
        {
            best = tmp;
            beta = tmp.score;
            if(firstStep)
            {
                best.pos = iter->first;
            }
        }
        if (tmp.score > alpha/* &&!firstStep*/)
        {
            break;
        }
    }
    return best;
}



grade Ai::iterative_deepening(Chessboard chessboard, int depth, int role)
{
    grade tmp, best;
    best.score = INT_MIN;
    for(int i = 2;i <= depth; i += 2)
    {
      tmp = max_alphabeta(chessboard, i, INT_MIN, INT_MAX, role, true);
      if(tmp.score > best.score)
          best = tmp;
    }
//    best = max_alphabeta(chessboard, depth, INT_MIN, INT_MAX, role, true);
    qDebug() << best.pos.x() << ',' << best.pos.y() << ' ' << best.score;
    return best;
}
