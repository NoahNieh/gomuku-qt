#include "ai.h"
#include <QDebug>

Ai::Ai()
{
    this->time = 0;
    this->win = 0;

}

Ai::Ai(int role)
{
    this->time = 0;
    this->win = 0;
    this->role = role;
}




QPoint Ai::generateNextStep(Chessboard chessboard,int difficulty, int role)
{
    int deep = 2 * difficulty;
    grade best = iterative_deepening(chessboard, deep, role==1?2:1);
    return best.pos;
}

grade Ai::min_alphabeta(Chessboard chessboard, int depth, int alpha, int beta, int role,bool considerDeep)
    {
        grade best;
        best.score = INT_MAX;
        std::vector<std::pair<QPoint, int> > nextstep = chessboard.generateNextStep(role == 1 ? 2:1, considerDeep);
        for(std::vector<std::pair<QPoint, int> >::iterator iter = nextstep.begin(); iter != nextstep.end(); iter++)
        {
            chessboard.setChess(iter->first, role == 1 ? 2:1);
            grade tmp = max_alphabeta(chessboard, depth-1, alpha, beta, role == 1 ? 2:1, considerDeep, false);
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


    /*max层 电脑考虑最好的情况(评估分数最高)*/
grade Ai::max_alphabeta(Chessboard chessboard, int depth, int alpha, int beta, int role, bool considerDeep, bool firstStep)
    {
        int res = chessboard.evaluateSituation(role);
        qDebug() << res;
        grade best;
        best.score = INT_MIN;
        if (res >= 100000000 && firstStep == false) //如果是第一步进来直接返回会没有棋子信息
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
        for(std::vector<std::pair<QPoint, int> >::iterator iter = nextstep.begin(); iter != nextstep.end(); iter++)
        {
            //debug
            if(firstStep)
            {
                qDebug() << iter->first.x() << ',' << iter->first.y();
            }
            chessboard.setChess(iter->first, role);
            //grade tmp = min_alphabeta(chessboard, depth-1, alpha, best.score>beta?best.score:beta, role, considerDeep); //修改
            grade tmp = min_alphabeta(chessboard, depth-1, alpha, beta, role == 1 ? 2:1, considerDeep);
            chessboard.setChess(iter->first, 0);
            if(firstStep == true)
            {
                best.pos = iter->first;
                best.score = tmp.score; //@noahnieh
            }
            if (tmp.score > best.score)
            {
                best = tmp; // @noahnieh 需要记录分数, 主调函数iterative_deepening中需要用分数来进行判断
                beta = tmp.score;
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
    grade tmp, best;
    best.score = INT_MIN;
    for(int i = 2;i <= depth; i += 2)
    {
      tmp = max_alphabeta(chessboard, i, INT_MIN, INT_MAX, role, false, true);
      if(best.score >= 100000000)
          break;
      else if(tmp.score > best.score)
          best = tmp;
    }
    qDebug() << best.pos.x() << ',' << best.pos.y() << ' ' << best.score;
    return best;
}
