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
    if((event->pos().x() < 30 || event->pos().x() > 783 || event->pos().y() < 30 || event->pos().y() > 784) && event->button() == Qt::LeftButton)
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
    if(event->pos().x() < 30 || event->pos().x() > 783 || event->pos().y() < 30 || event->pos().y() > 784)
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

    if(judge->putChess(pos) == 1)
    {
        judge->resetJudge();
    }
    update();
    return;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/cb.png");
    painter.drawPixmap(0, 0, pix.width(), pix.height(), pix);
    Chessboard *chessboard = judge->getChessboard();
    if(chessboard == NULL) return;
    QPoint pos;
    for(pos.setX(0); pos.x()<15; pos.setX(pos.x()+1))
    {
        for(pos.setY(0); pos.y()<15; pos.setY(pos.y()+1))
        {
            if(chessboard->getChess(pos) != 0)
            {
                if(chessboard->getChess(pos) == 1)
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
            }
        }
    }
    return;
}

void MainWindow::on_playWithHum_clicked()
{
    judge->playWithHum();
}

void MainWindow::on_exit_clicked()
{
    this->close();
}
