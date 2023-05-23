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
    //création des boutons pour avancer
    void on_pushButton_2_pressed();
    void on_pushButton_2_released();

    //création des boutons pour tourner à droite
    void on_pushButton_3_pressed();
    void on_pushButton_3_released();

    //création des boutons pour reculer
    void on_pushButton_4_pressed();
    void on_pushButton_4_released();

    //création des boutons pour tourner à gauche
    void on_pushButton_pressed();
    void on_pushButton_released();

private:
    Ui::MainWindow *ui;
    MyRobot myrobot;

protected:
    void keyPressEvent(QKeyEvent *event) override //Réécriture de la fonction keyPressEvent pour nos besoins
    {
        if(event->key() == Qt::Key_Z)//Touche Z du clavier pressé
        {
           myrobot.move_forward();//Le robot avance
        }
        else if(event->key() == Qt::Key_D)//Si touche D du clavier pressé
        {
            myrobot.turn_right();//Le robot tourne à droite
        }
        else if(event->key() == Qt::Key_S)//Si touche S du clavier pressé
        {
            myrobot.move_backward();//Le robot recule
        }
        else if(event->key() == Qt::Key_Q)//Si touche Q du clavier pressé
        {
            myrobot.turn_left();//Le robot tourne à gauche
        }
        QMainWindow::keyPressEvent(event);
    }
    void keyReleaseEvent(QKeyEvent *event) override //Réécriture de la fonction keyReleaseEvent pour nos besoins
    { //si les touches ZQSD sont relâché, le robot s'arrête là où il est
        if(event->key() == Qt::Key_Z)
        {
            myrobot.stop();
        }
        else if(event->key() == Qt::Key_D)
        {
            myrobot.stop();
        }
        else if(event->key() == Qt::Key_S)
        {
            myrobot.stop();
        }
        else if(event->key() == Qt::Key_Q)
        {
            myrobot.stop();
        }
        QMainWindow::keyReleaseEvent(event);
    }

};
#endif // MAINWINDOW_H
