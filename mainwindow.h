#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QAbstractSocket>
#include <judge.h>
#include <network.h>
#include <stack>

class QTcpSocket;
class QTcpServer;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Judge *judge;
    bool is_drag = false;
    QPoint mouse_position;
    QParallelAnimationGroup winner_animation;
    QTimer timer;
    QTimer delay;
    double opacity = 0;
    bool fade_in = true;
    int status = 0; //0 disconnect, 1 connected 2 listening
    QGraphicsOpacityEffect *effect;
    QTcpServer *tcp_server;
    QTcpSocket *tcp_client;
    int client_num = 0;
    NetWork *network;
    quint16 block_size;

signals:
    void putChess(QPoint pos);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void on_playWithHum_clicked();
    void on_exit_clicked();
    void on_playWithCom_clicked();
    void fadeInFadeOut();
    void startFadeOut();
    void createServer(int port);
    void connectServerSlot(QString address, int port);
    void getConnect();
    void gameStart();
    void sendChess(QPoint pos);
    void readChess();
    void disconnected();
    void error(QAbstractSocket::SocketError);
};

#endif // MAINWINDOW_H
