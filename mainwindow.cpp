#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , myrobot(parent)

{
    ui->setupUi(this);
    myrobot.doConnect();

}

MainWindow::~MainWindow()
{
    myrobot.disConnect();
    delete ui;
}

void MainWindow::on_pushButton_2_pressed()
{
    myrobot.move_forward();
}
void MainWindow::on_pushButton_2_released()
{
    myrobot.stop();
}

void MainWindow::on_pushButton_3_pressed()
{
    myrobot.turn_right();
}
void MainWindow::on_pushButton_3_released()
{
    myrobot.stop();
}

void MainWindow::on_pushButton_4_pressed()
{
    myrobot.move_backward();
}
void MainWindow::on_pushButton_4_released()
{
    myrobot.stop();
}

void MainWindow::on_pushButton_pressed()
{
    myrobot.turn_left();
}
void MainWindow::on_pushButton_released()
{
    myrobot.stop();
}
