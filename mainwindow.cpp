#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , myrobot(parent)

{
    ui->setupUi(this);
    myrobot.info();
    myrobot.getIR();

}

MainWindow::~MainWindow()
{
    delete ui;
}
//ajout du mouvement lorsque l'on presse le bouton ou non

void MainWindow::on_pushButton_2_pressed()//Pressage du bouton "Haut"
{
    myrobot.move_forward();
    this->ui->progressBar->setValue((myrobot.getBat()/205)*100);

}
void MainWindow::on_pushButton_2_released()//Relâchage du bouton "Haut"
{
    myrobot.stop();
    this->ui->progressBar->setValue((myrobot.getBat()/205)*100);
}

void MainWindow::on_pushButton_3_pressed()//Pressage du bouton "Droite"
{
    myrobot.turn_right();
    this->ui->progressBar->setValue((myrobot.getBat()/205)*100);
}
void MainWindow::on_pushButton_3_released()//Relâchage du bouton "Droite"
{
    myrobot.stop();
    this->ui->progressBar->setValue((myrobot.getBat()/205)*100);
}

void MainWindow::on_pushButton_4_pressed()//Pressage du bouton "Bas"
{
    myrobot.move_backward();
    this->ui->progressBar->setValue((myrobot.getBat()/205)*100);
}
void MainWindow::on_pushButton_4_released()//Relâchage du bouton "Bas"
{
    myrobot.stop();
    this->ui->progressBar->setValue((myrobot.getBat()/205)*100);
}

void MainWindow::on_pushButton_pressed()//Pressage du bouton "Gauche"
{
    myrobot.turn_left();
    this->ui->progressBar->setValue((myrobot.getBat()/205)*100);
}
void MainWindow::on_pushButton_released()//Relâchage du bouton "Gauche"
{
    myrobot.stop();
    this->ui->progressBar->setValue((myrobot.getBat()/205)*100);
}
/*void MainWindow::on_pushButton_7_clicked()
{
    myrobot.augmenterVitesse();
}


void MainWindow::on_pushButton_5_clicked()
{
    myrobot.diminuerVitesse();
}*/


void MainWindow::on_pushButton_5_clicked() //Bouton connexion
{
    myrobot.doConnect();
    this->ui->progressBar->setValue((myrobot.getBat()/205)*100);
    //this->ui->lcdNumber_2->display(myrobot.getIR());

}


void MainWindow::on_pushButton_6_clicked() //Bouton deconnexion
{
    myrobot.disConnect();
    this->ui->progressBar->setValue(0);
    this->ui->lcdNumber->display(0);
    this->ui->lcdNumber_2->display(0);
}

