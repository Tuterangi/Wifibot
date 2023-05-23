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
//ajout du mouvement lorsque l'on presse le bouton ou non

void MainWindow::on_pushButton_2_pressed()//Pressage du bouton "Haut"
{
    myrobot.move_forward();
}
void MainWindow::on_pushButton_2_released()//Relâchage du bouton "Haut"
{
    myrobot.stop();
}

void MainWindow::on_pushButton_3_pressed()//Pressage du bouton "Droite"
{
    myrobot.turn_right();
}
void MainWindow::on_pushButton_3_released()//Relâchage du bouton "Droite"
{
    myrobot.stop();
}

void MainWindow::on_pushButton_4_pressed()//Pressage du bouton "Bas"
{
    myrobot.move_backward();
}
void MainWindow::on_pushButton_4_released()//Relâchage du bouton "Bas"
{
    myrobot.stop();
}

void MainWindow::on_pushButton_pressed()//Pressage du bouton "Gauche"
{
    myrobot.turn_left();
}
void MainWindow::on_pushButton_released()//Relâchage du bouton "Gauche"
{
    myrobot.stop();
}
