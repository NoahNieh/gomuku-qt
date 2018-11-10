#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "judge.h"
#include "ai.h"
#include <QDebug>
#include <assert.h>
#include <QPainter>
#include <QPixmap>
#include <QtNetwork>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->network = new NetWork();
//    this->tcp_client = new QTcpSocket(this);
    this->tcp_client = NULL;
    this->tcp_server = new QTcpServer(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(0.95);
    this->ui->winner->hide();
    this->ui->winner->setAttribute(Qt::WA_TranslucentBackground, true);
    this->effect=new QGraphicsOpacityEffect();
    this->effect->setOpacity(this->opacity);
    this->ui->winner->setGraphicsEffect(this->effect);
    this->judge = new Judge();
    this->block_size = 0;
    this->ui->disconnect->hide();
    this->status = 0;

    connect(&(this->timer), SIGNAL(timeout()), this, SLOT(fadeInFadeOut()));
    connect(&(this->delay), SIGNAL(timeout()), this, SLOT(startFadeOut()));
//    connect(this->tcp_client, &QTcpSocket::readyRead, this, &MainWindow::readChess);
    connect(this->network, SIGNAL(createServer(int)), this, SLOT(createServer(int)));
    connect(this, SIGNAL(putChess(QPoint)), this, SLOT(sendChess(QPoint)));
    connect(this->network, SIGNAL(connectServer(QString,int)), this, SLOT(connectServerSlot(QString,int)));
}

void MainWindow::fadeInFadeOut()
{
//    qDebug() << this->opacity;
    if(this->opacity < 1 && this->fade_in == true)
    {
        this->opacity += 0.01;
        this->ui->winner->setGeometry(280-140*this->opacity, 680-140*this->opacity, 441-200*this->opacity, 271-200*this->opacity);
        this->ui->winner->setFont(QFont("楷体", 135-100*this->opacity, QFont::Bold));
        this->effect->setOpacity(this->opacity);
        this->ui->winner->setGraphicsEffect(this->effect);
    }
    else if(this->opacity > 0 && this->fade_in == false)
    {
        this->opacity -= 0.01;
        this->ui->winner->setGeometry(280-140*this->opacity, 680-140*this->opacity, 441-200*this->opacity, 271-200*this->opacity);
        this->ui->winner->setFont(QFont("楷体", 135-100*this->opacity, QFont::Bold));
        this->effect->setOpacity(this->opacity);
        this->ui->winner->setGraphicsEffect(this->effect);
    }
    else if(this->opacity > 1)
    {
        this->fade_in = false;
        this->timer.stop();
        this->delay.start(2000);
    }
    else if(this->opacity < 0)
    {
        this->fade_in = true;
        this->judge->setWinner(0);
        this->ui->winner->hide();
        this->timer.stop();
    }
}

void MainWindow::startFadeOut()
{
    this->timer.start(4);
    this->delay.stop();
}

void MainWindow::createServer(int port)
{
//    this->tcp_server = new QTcpServer(this);
    if(this->tcp_server->isListening()) tcp_server->close();
    if(this->tcp_server->isListening()) return;
    this->tcp_server->listen(QHostAddress::Any, port);
    connect(this->tcp_server, &QTcpServer::newConnection, this, &MainWindow::getConnect);
    this->status = 2;
    this->ui->status->setText("等待连接");
//    this->ui->disconnect->show();
    this->judge->setGameMode(3);
}

void MainWindow::connectServerSlot(QString address, int port)
{
    block_size =  0;
    this->tcp_client = new QTcpSocket(this);
    connect(this->tcp_client, &QTcpSocket::readyRead, this, &MainWindow::readChess);
    this->tcp_client->abort();
    qDebug() << address;
//    this->ui->disconnect->show();
    this->tcp_client->connectToHost(address, port);
    this->ui->status->setText("正在连接");
    if(this->tcp_client->waitForConnected(10000))
    {
        this->ui->status->setText("已连接");
        this->status = 1;
        this->ui->playWithHum->setText("断开");

    }
    else
    {
        this->ui->status->setText("连接失败");
        return;
    }
    connect(this->tcp_client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    connect(this->tcp_client, &QTcpSocket::disconnected, this->tcp_client, &QTcpSocket::deleteLater);
    connect(this->tcp_client, &QTcpSocket::disconnected, this, &MainWindow::disconnected);
    this->judge->playWithHum(2);
}

void MainWindow::getConnect()
{
//    if(client_num != 0) return; // 需要发出错误信号
    if(this->status != 2) return;
    this->tcp_client = new QTcpSocket(this);
    connect(this->tcp_client, &QTcpSocket::readyRead, this, &MainWindow::readChess);
    this->tcp_client = this->tcp_server->nextPendingConnection();
    this->tcp_server->close();
    this->ui->status->setText("已连接");
    this->status = 1;
    this->ui->playWithHum->setText("断开");
    qDebug() << "get connect";
    connect(this->tcp_client, &QTcpSocket::disconnected, this->tcp_client, &QTcpSocket::deleteLater);
    connect(this->tcp_client, &QTcpSocket::disconnected, this, &MainWindow::disconnected);
//    connect(this->tcp_client, &QTcpSocket::disconnected, this, &MainWindow::on_disconnect_clicked);
    connect(this->tcp_client, &QTcpSocket::readyRead, this, &MainWindow::readChess);
    gameStart();

}

void MainWindow::gameStart()
{
    this->judge->playWithHum(1);
    this->timer.stop();
    this->delay.stop();
    this->ui->winner->hide();
    this->opacity = 0;
    this->fade_in = true;
    update();
}

void MainWindow::sendChess(QPoint pos)
{
//    qDebug() << pos.x() << pos.y();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_5_9);
    out<<(quint16)0;
    out << pos;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    this->tcp_client->write(block);
}

void MainWindow::readChess()
{
    QPoint pos(-2, -2);
    qDebug() << this->tcp_client->bytesAvailable();
    qDebug() << (int)sizeof(quint16);
    qDebug() << block_size;
    QDataStream in(this->tcp_client);
    in.setVersion(QDataStream::Qt_5_9);
    if(this->block_size == 0)
    {
        if(this->tcp_client->bytesAvailable() < (int)sizeof(quint16))
        {
            return;
        }
        in >> this->block_size;
    }
    if(this->tcp_client->bytesAvailable() < this->block_size)
    {
        return;
    }
    in >> pos;
    if(pos.x() != -2)
    {
        if(pos.x() == -1)
        {
            this->judge->setWinner(this->judge->getTerm());
            this->judge->resetJudge();
        }
        else
        {
            this->judge->putChess(pos);
        }
    }
    this->block_size = 0;
    update();
}

void MainWindow::disconnected()
{
    this->tcp_client->disconnectFromHost();
    this->tcp_client->waitForConnected(10000);
    this->tcp_client->close();
    this->ui->status->setText("未连接");
    this->ui->playWithHum->setText("playWithHum");
    this->status = 0;
    this->judge->resetJudge();
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
//    qDebug() << event->pos();
    //棋盘外
    if(event->pos().x() < 30 || event->pos().x() > 736 || event->pos().y() < 30 || event->pos().y() > 736)
    {
        is_drag = false;
        return;
    }

    //棋盘内
    if(this->judge->getGameMode() == 0 || !(this->judge->isYourTerm()) || this->judge->getGameMode() == 3) return;
    QPoint pos = event->pos();
    pos.setX((pos.x()-8) / 50);
    pos.setY((pos.y()-9) / 50);
    int flag;
    if((flag = this->judge->putChess(pos)) == 1)
    {
        emit putChess(QPoint(-1, -1));
        this->judge->resetJudge();
    }
    else
    {
        emit putChess(pos);
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
    QFont font("Lucida Console", 9, QFont::Bold);
    painter.setFont(font);
    for(std::stack<QPoint> tmp = chessboard->getHistory(); !tmp.empty(); tmp.pop())
    {
        if(chessboard->getChess(tmp.top()) != 0)
        {
            QPoint pos = QPoint(tmp.top().x(), tmp.top().y());
            if(chessboard->getChess(tmp.top()) == 1)
            {
//                painter.setPen(QColor(Qt::black));
//                painter.setBrush(QBrush(Qt::black));
                QPixmap pix;
                pix.load(":/image/image/b2.png");
                painter.drawPixmap(33+pos.x()*50-20, 33+pos.y()*50-20, 40, 40, pix);
            }
            else
            {
//                painter.setPen(QColor(Qt::white));
//                painter.setBrush(QBrush(Qt::white));
                QPixmap pix;
                pix.load(":/image/image/w2.png");
                painter.drawPixmap(33+pos.x()*50-20, 33+pos.y()*50-20, 40, 40, pix);
            }
//            painter.drawEllipse(33+pos.x()*50-20, 33+pos.y()*50-20, 40, 40);
            painter.setPen(QColor(Qt::red));
            painter.drawText(33+pos.x()*50-25, 33+pos.y()*50-25, 50, 50,Qt::AlignCenter ,QString::number(tmp.size(),10));
        }
    }

    //win info
    if(this->judge->getWinner() != 0)
    {

        if(this->judge->getWinner() == 1)
        {
            this->ui->winner->setText("黑棋胜利");
        }
        else
        {
            this->ui->winner->setText("白棋胜利");
        }
        this->ui->winner->show();
        this->timer.start(4);

    }

    return;
}

void MainWindow::on_playWithHum_clicked()
{
//    this->judge->playWithHum();
    if(this->status != 0)
    {
        this->tcp_client->disconnectFromHost();
        this->disconnected();
        return;
    }
    this->timer.stop();
    this->delay.stop();
    this->ui->winner->hide();
    this->opacity = 0;
    this->fade_in = true;
    update();
    this->network->show();

}

void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::on_playWithCom_clicked()
{
    this->judge->playWithCom(1);
    this->timer.stop();
    this->delay.stop();
    this->ui->winner->hide();
    this->opacity = 0;
    this->fade_in = true;
    update();
}

//useless
void MainWindow::on_disconnect_clicked()
{
    this->tcp_client->disconnectFromHost();
    if(this->tcp_server->isListening()) this->tcp_server->close();
    this->client_num = 0;
    this->ui->disconnect->hide();
}

void MainWindow::error(QAbstractSocket::SocketError e)
{
    qDebug() << e;
}
