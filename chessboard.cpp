#include "chessboard.h"

Chessboard::Chessboard()
{
    for(int i = 0; i<15; i++)
    {
        for(int j = 0; j<15; j++)
        {
            chessboard[i][j] = 0;
            scoreOfComputer[i][j] = 0;
            scoreOfHuman[i][j] = 0;
        }
    }
}

int Chessboard::setChess(QPoint pos, int role)
{
    chessboard[pos.x()][pos.y()] = role;
    return 0;
}



int Chessboard::getChess(QPoint pos)
{
    if(pos.x()>=15 || pos.x()<0 || pos.y()<0 || pos.y()>=15) return 0;
    return this->chessboard[pos.x()][pos.y()];
}


int Chessboard::evaluateSituation()
{
    QPoint pos;
    for(int i = 0; i<15; i++)
    {
        pos.setX(i);
        for(int j = 0; j<15; j++)
        {
            pos.setY(j);
            if(chessboard[i][j] == 0)
            {
                if(hasNeighbor(pos,2,2)){
                    scoreOfComputer[i][j] = scorePoint(pos,1);
                    scoreOfHuman[i][j] = scorePoint(pos,2);
                }
            }
            else if(chessboard[i][j] == 1)
            {
                scoreOfComputer[i][j] = scorePoint(pos,1);
                scoreOfHuman[i][j] = 0;
            }
            else if(chessboard[i][j] == 2)
            {
                scoreOfComputer[i][j] = 0;
                scoreOfHuman[i][j] = scorePoint(pos,2);
            }

        }
    }
    return 0;
}

bool Chessboard::hasNeighbor(QPoint pos, int distance, int count)
{
    int startX = pos.x()-distance;
    int endX = pos.x()+distance;
    int startY = pos.y()-distance;
    int endY = pos.y()+distance;

    for(int i = startX; i<=endX; i++)
    {
        if(i<0||i>=15) continue;
        for(int j = startY; j<=endY; j++){
            if(j<0||j>=15) continue;
            if(i==pos.x() && j==pos.y()) continue;
            if(chessboard[i][j] != 0){
                count--;
                if(count <= 0)
                    return true;
            }
        }
    }
    return false;
}

int Chessboard::scorePoint(QPoint pos, int role)
{
    int totalScore = 0;
    int count = 1;
    int block = 0;
    int empty = -1;

    //|
    for(int j = pos.y()+1; ; j++)
    {
        if(j>14)
        {
            block++;
            break;
        }
        if(chessboard[pos.x()][j] == 0)
        {
            if(empty == -1 && j < 14 && chessboard[pos.x()][j+1] == role){
                empty = count;
                continue;
            }
            else
            {
                break;
            }
        }
        if(chessboard[pos.x()][j] == role)
        {
            count++;
            continue;
        }
        else
        {
            block++;
            break;
        }
    }

    for(int j = pos.y()-1; ; j--)
    {
        if(j<0)
        {
            block++;
            break;
        }
        if(chessboard[pos.x()][j] == 0)
        {
            if(empty == -1 && j > 0 && chessboard[pos.x()][j-1] == role){
                empty = 0;
                continue;
            }
            else
            {
                break;
            }
        }
        if(chessboard[pos.x()][j] == role)
        {
            count++;
            if(empty != -1)
            {
                empty++;
            }
            continue;
        }
        else
        {
            block++;
            break;
        }
    }

    totalScore += countToScore(count, block, empty);


    //-
    count = 1;
    block = 0;
    empty = -1;

    for(int i = pos.x()+1;;i++)
    {
        if(i>14)
        {
            block++;
            break;
        }
        if(chessboard[i][pos.y()] == 0)
        {
            if(empty == -1 && i < 14 && chessboard[i+1][pos.y()] == role){
                empty = count;
                continue;
            }
            else
            {
                break;
            }
        }
        if(chessboard[i][pos.y()] == role)
        {
            count++;
            continue;
        }
        else
        {
            block++;
            break;
        }
    }

    for(int i = pos.x()-1;;i--)
    {
        if(i<0)
        {
            block++;
            break;
        }
        if(chessboard[i][pos.y()] == 0)
        {
            if(empty == -1 && i > 0 && chessboard[i-1][pos.y()] == role){
                empty = 0;
                continue;
            }
            else
            {
                break;
            }
        }
        if(chessboard[i][pos.y()] == role)
        {
            count++;
            if(empty != -1)
            {
                empty++;
            }
            continue;
        }
        else
        {
            block++;
            break;
        }
    }

    totalScore += countToScore(count, block, empty);


    // \
    count = 1;
    block = 0;
    empty = -1;

    for(int i = 1; ; i++)
    {
        int x = pos.x()+i, y = pos.y()+i;
        if(x > 14 || y > 14)
        {
            block++;
            break;
        }
        if(chessboard[x][y] == 0)
        {
            if(empty == -1 && (x < 14 && y < 14) && chessboard[x+1][y+1] == role)
            {
                empty = count;
                continue;
            }
            else
            {
                break;
            }
        }
        if(chessboard[x][y] == role)
        {
            count++;
            continue;
        }
        else
        {
            block++;
            break;
        }
    }

    for(int i = 1;;i++)
    {
        int x = pos.x()-i, y = pos.y()-i;
        if(x < 0 || y < 0)
        {
            block++;
            break;
        }
        if(chessboard[x][y] == 0)
        {
            if(empty == -1 && (x > 0 && y > 0) && chessboard[x-1][y-1] == role)
            {
                empty = 0;
                continue;
            }
            else
            {
                break;
            }
        }
        if(chessboard[x][y] == role)
        {
            count++;
            if(empty != -1)
            {
                empty++;
            }
            continue;
        }
        else
        {
            block++;
            break;
        }
    }

    totalScore += countToScore(count, block, empty);


    // /
    count = 1;
    block = 0;
    empty = -1;

    for(int i = 1;;i++)
    {
        int x = pos.x()+i, y = pos.y()-i;
        if(x < 0 || y < 0 || x >14 || y > 14)
        {
            block++;
            break;
        }
        if(chessboard[x][y] == 0)
        {
            if(empty == -1 && (x < 14 && y < 14) && chessboard[x+1][y-1] == role)
            {
                empty = count;
                continue;
            }
            else
            {
                break;
            }
        }
        if(chessboard[x][y] == role)
        {
            count++;
            continue;
        }
        else
        {
            block++;
            break;
        }
    }

    for(int i = 1;;i++)
    {
        int x = pos.x()-1, y = pos.y()+1;
        if(x < 0 || y < 0 || x >14 || y > 14)
        {
            block++;
            break;
        }
        if(chessboard[x][y] == 0)
        {
            if(empty == -1 && (x > 0 && y > 0) && chessboard[x-1][y+1] == role)
            {
                empty = 0;
                continue;
            }
            else
            {
                break;
            }
        }
        if(chessboard[x][y] == role)
        {
            count++;
            if(empty != -1)
            {
                empty++;
            }
            continue;
        }
        else
        {
            block++;
            break;
        }
    }

    totalScore += countToScore(count, block, empty);

    return totalScore;
}

int Chessboard::countToScore(int count, int block, int empty)
{
    if(empty <= 0)
    {
        if(count >= 5) return FIVE;
        if(block == 0)
        {
            switch(count)
            {
                case 1: return  ONE;
                case 2: return TWO;
                case 3: return THREE;
                case 4: return FOUR;
            }
        }
        if(block == 1)
        {
            switch(count)
            {
                case 1: return  BLOCKED_ONE;
                case 2: return BLOCKED_TWO;
                case 3: return BLOCKED_THREE;
                case 4: return BLOCKED_FOUR;
            }
        }
    }
    else if(empty == 1 || empty == count-1)
    {
        if(count >= 6) return FIVE;
        if(block == 0)
        {
            switch(count)
            {
                case 2: return TWO/2;
                case 3: return THREE;
                case 4: return BLOCKED_FOUR;
                case 5: return FOUR;
            }
        }
        if(block == 1)
        {
            switch(count)
            {
                case 2: return BLOCKED_TWO;
                case 3: return BLOCKED_THREE;
                case 4: return BLOCKED_FOUR;
                case 5: return BLOCKED_FOUR;
            }
        }
    }
    else if(empty ==2 || empty == count -2)
    {
        if(count >= 7) return FIVE;
        if(block == 0)
        {
            switch(count)
            {
                case 3: return THREE;
                case 4:
                case 5: return BLOCKED_FOUR;
                case 6: return FOUR;
            }
        }
        if(block == 1)
        {
            switch(count)
            {
                case 3: return BLOCKED_THREE;
                case 4: return BLOCKED_FOUR;
                case 5: return BLOCKED_FOUR;
                case 6: return FOUR;
            }
        }
        if(block == 2)
        {
            switch(count)
            {
                case 4:
                case 5:
                case 6: return BLOCKED_FOUR;
            }
        }
    }
    else if(empty == 3 || empty == count-3)
    {
        if(count >= 8) return FIVE;
        if(block == 0)
        {
            switch(count)
            {
                    case 4:
                    case 5: return THREE;
                    case 6: return BLOCKED_FOUR;
                    case 7: return FOUR;
            }
        }
        if(block == 1)
        {
            switch(count)
            {
                case 4:
                case 5:
                case 6: return BLOCKED_FOUR;
                case 7: return FOUR;
            }
        }
        if(block == 2)
        {
            switch(count)
            {
                case 4:
                case 5:
                case 6:
                case 7: return BLOCKED_FOUR;
            }
        }
    }
    else if(empty == 4 || empty == count-4)
    {
        if(count >= 9) return FIVE;
        if(block == 0)
        {
            switch(count)
            {
                    case 5:
                    case 6:
                    case 7:
                    case 8: return FOUR;
            }
        }
        if(block == 1)
        {
            switch(count)
            {
                case 4:
                case 5:
                case 6:
                case 7: return BLOCKED_FOUR;
                case 8: return FOUR;
            }
        }
        if(block == 2)
        {
            switch(count)
            {
                case 5:
                case 6:
                case 7:
                case 8: return BLOCKED_FOUR;
            }
        }
    }
    else if(empty == 5 || empty == count -5)
    {
        return FIVE;
    }

    return 0;
}




















