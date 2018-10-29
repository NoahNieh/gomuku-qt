#include "ai.h"

Ai::Ai()
{

}

QPoint Ai::generateNextStep(Chessboard chessboard,int difficulty, int role)
{
    int deep = 2 * difficulty;
    grade best = Ai::iterative_deepening(chessboard, deep, role);
    return best.pos;
}

grade Ai::min_alphabeta(Chessboard chessboard, int depth, int alpha, int beta, int role,bool considerDeep)
    {
        grade best;
        best.score = INT_MAX;
        std::vector<std::pair<QPoint, int> > nextstep = chessboard.generateNextStep(role == 1 ? 2:1, considerDeep);
        for(std::vector<std::pair<QPoint, int> >::iterator iter = nextstep.begin(); iter < nextstep.end(); iter++)
        {
            chessboard.setChess(iter->first, role == 1 ? 2:1);
            grade tmp = max_alphabeta(chessboard, depth-1, best.score < alpha ? best.score : alpha, beta,role == 1 ? 2:1, considerDeep, false);
            chessboard.setChess(iter->first, 0);
            if (tmp.score < best.score)
            {
                best = tmp;
            }
            if (tmp.score < beta)
            {
                break;
            }
        }
        return best;
    }


    /*max层 电脑考虑最好的情况(评估分数最高)*/
grade Ai::max_alphabeta(Chessboard chessboard, int depth, int alpha, int beta, int role, bool considerDeep, bool firstStep)
    {
        int res = chessboard.evaluateSituation(role);
        grade best;
        best.score = INT_MIN;
        if (res >= 10000000)
        {
            best.score = res;
            return best;
        }
        else if(depth <= 0 && considerDeep == false)
        {
            considerDeep = true;
            depth = 4;
        }
        else if(depth <= 0 && considerDeep == true)
        {
            best.score = res;
            return best;
        }
        std::vector<std::pair<QPoint, int> > nextstep = chessboard.generateNextStep(role, considerDeep);
        for(std::vector<std::pair<QPoint, int> >::iterator iter = nextstep.begin(); iter < nextstep.end(); iter++)
        {
            chessboard.setChess(iter->first, role);
            grade tmp = Ai::min_alphabeta(chessboard, depth-1, alpha, best.score>beta?best.score:beta, role, considerDeep);
            chessboard.setChess(iter->first, 0);
            if(firstStep == true)
            {
                best.pos = iter->first;
            }
            if (tmp.score > best.score)
            {
                best = tmp;
            }
            if (tmp.score > alpha)
            {
                break;
            }
        }
        return best;
    }

grade Ai::iterative_deepening(Chessboard chessboard, int depth, int role)
{
    grade tmp,best;
    best.score = INT_MIN;
    for(int i = 2;i <= depth; i += 2)
    {
      tmp = Ai::max_alphabeta(chessboard, i, INT_MIN, INT_MAX, role, false, true);
      if(best.score >= 10000000)
          break;
      else if(tmp.score > best.score)
          best = tmp;
    }
    return best;
}
