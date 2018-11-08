#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>
#include <QString>

namespace Ui {
class NetWork;
}

class NetWork : public QWidget
{
    Q_OBJECT

public:
    explicit NetWork(QWidget *parent = 0);
    ~NetWork();

signals:
    void createServer(int port);
    void connectServer(QString address, int port);

private slots:
    void on_create_clicked();

    void on_connect_clicked();

    void on_exit_clicked();

private:
    Ui::NetWork *ui;
};

#endif // NETWORK_H
