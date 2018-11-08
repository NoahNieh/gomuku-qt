#include "network.h"
#include "ui_network.h"

NetWork::NetWork(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetWork)
{
    ui->setupUi(this);
}

NetWork::~NetWork()
{
    delete ui;
}

void NetWork::on_create_clicked()
{
    emit createServer(this->ui->port->text().toInt());
    this->hide();
}

void NetWork::on_connect_clicked()
{
    emit connectServer(this->ui->address->text(), this->ui->port->text().toInt());
    this->hide();
}

void NetWork::on_exit_clicked()
{
    this->hide();
}
