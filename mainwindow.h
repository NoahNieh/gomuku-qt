#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <judge.h>
#include <stack>

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
    QGraphicsOpacityEffect *effect;

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
};

#endif // MAINWINDOW_H
