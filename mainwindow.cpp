#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "judge.h"
#include "ai.h"
#include <QDebug>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(0.95);
    judge = new Judge();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if((event->pos().x() < 30 || event->pos().x() > 736 || event->pos().y() < 30 || event->pos().y() > 736) && event->button() == Qt::LeftButton)
    {
        is_drag = true;
        mouse_position = event->globalPos() - this->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(is_drag && (event->buttons() && Qt::LeftButton))
    {
        this->move(event->globalPos() - mouse_position);
    }
}



// (33,34)
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //棋盘外
    if(event->pos().x() < 30 || event->pos().x() > 736 || event->pos().y() < 30 || event->pos().y() > 736)
    {
        is_drag = false;
        return;
    }

    //棋盘内
    if(judge->getGameMode() == 0 || typeid(judge->getPlayer(judge->getTerm())) == typeid(Ai))
    {
        return;
    }
    QPoint pos = event->pos();
    pos.setX((pos.x()-8) / 50);
    pos.setY((pos.y()-9) / 50);
    int flag;
    if((flag = this->judge->putChess(pos)) == 1)
    {
        this->judge->resetJudge();
    }
    update();
    if(this->judge->getGameMode() == 1 && flag != -1)
    {
        QPoint next_step = this->judge->putChessAi();
        if(this->judge->putChess(next_step) == 1)
        {
            this->judge->resetJudge();
        }

    }
    update();
    return;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/image/cb.png");
    painter.drawPixmap(0, 0, pix.width(), pix.height(), pix);
    Chessboard *chessboard = judge->getChessboard();
    if(chessboard == NULL) return;
    QPoint pos;
//    for(pos.setX(0); pos.x()<15; pos.setX(pos.x()+1))
//    {
//        for(pos.setY(0); pos.y()<15; pos.setY(pos.y()+1))
//        {
//            if(chessboard->getChess(pos) != 0)
//            {
//                if(chessboard->getChess(pos) == 1)
//                {
//                    painter.setPen(QColor(Qt::black));
//                    painter.setBrush(QBrush(Qt::black));
//                }
//                else
//                {
//                    painter.setPen(QColor(Qt::white));
//                    painter.setBrush(QBrush(Qt::white));
//                }
//                painter.drawEllipse(22+pos.x()*50, 23+pos.y()*50, 23, 23);
//            }
//        }
//    }
    for(std::stack<QPoint> tmp = chessboard->getHistory(); !tmp.empty(); tmp.pop())
    {
        if(chessboard->getChess(tmp.top()) != 0)
        {
            QPoint pos = QPoint(tmp.top().x(), tmp.top().y());
            if(chessboard->getChess(tmp.top()) == 1)
            {
                painter.setPen(QColor(Qt::black));
                painter.setBrush(QBrush(Qt::black));
            }
            else
            {
                painter.setPen(QColor(Qt::white));
                painter.setBrush(QBrush(Qt::white));
            }
            painter.drawEllipse(22+pos.x()*50, 23+pos.y()*50, 23, 23);
            painter.setPen(QColor(Qt::red));
            painter.drawText(22+pos.x()*50+7, 23+pos.y()*50+15, QString::number(tmp.size(),10));
        }
    }
    return;
}

void MainWindow::on_playWithHum_clicked()
{
    this->judge->playWithHum();
}

void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::on_playWithCom_clicked()
{
    this->judge->playWithCom(1);
    update();
}
