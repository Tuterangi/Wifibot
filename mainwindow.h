#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <myrobot.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_pressed();
    void on_pushButton_2_released();

    void on_pushButton_3_pressed();
    void on_pushButton_3_released();

    void on_pushButton_4_pressed();
    void on_pushButton_4_released();

    void on_pushButton_pressed();
    void on_pushButton_released();

private:
    Ui::MainWindow *ui;
    MyRobot myrobot;

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        if(event->key() == Qt::Key_Z)
        {
            myrobot.move_forward();
        }
        else if(event->key() == Qt::Key_D)
        {
            myrobot.turn_right();
        }
        else if(event->key() == Qt::Key_S)
        {
            myrobot.move_backward();
        }
        else if(event->key() == Qt::Key_Q)
        {
            myrobot.turn_left();
        }
        else
        {
            myrobot.stop();
        }

    }

};
#endif // MAINWINDOW_H
