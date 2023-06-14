#include "myrobot.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void printVideo(QWebEngineView *video);
    void camRight();
    void camLeft();
    void camUp();
    void camDown();

    void brightness();
    QNetworkAccessManager *manager;

private slots:

    void on_right_clicked();

    void on_Up_clicked();

    void on_Left_clicked();

    void on_Down_clicked();

private:
    Ui::MainWindow *ui;
    MyRobot bot;
};

#endif // MAINWINDOW_H
