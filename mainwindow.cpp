#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , myrobot(parent)

{
    ui->setupUi(this);
    myrobot.info();

}

MainWindow::~MainWindow()
{
    delete ui;
}
//ajout du mouvement lorsque l'on presse le bouton ou non

void MainWindow::odometrie(){
    QString OL = QString::number(myrobot.getOdometryL()); //On récupère la position de la roue Gauche
    QString OR = QString::number(myrobot.getOdometryR()); //On récupère la position de la roue Droite
    this->ui->label_5->setText((QString) OL); //On affiche la position de la roue Gauche
    this->ui->label_6->setText((QString) OR); //On affiche la position de la roue Droite
}

void MainWindow::vitesse(){
    long odometrie_diffL = myrobot.getOdometryL() - myrobot.getLastOdometryL();
    long odometrie_diffR = myrobot.getOdometryR() - myrobot.getLastOdometryR();
    int nb_tics = 2048;
    float temps = 0.075;
    float perimetre = 0.44;
    float VL = ((odometrie_diffL * perimetre)/nb_tics)/temps;
    float VR = ((odometrie_diffR * perimetre)/nb_tics)/temps;
    this->ui->lcdNumber->display(VL);
    this->ui->lcdNumber_3->display(VR);
    qDebug() << "odometrie : " << (myrobot.getOdometryL()-myrobot.getLastOdometryL());
}

void MainWindow::infrarouge(){
    unsigned char IRLF = myrobot.getIRLF();
    unsigned char IRLB = myrobot.getIRLB();
    unsigned char IRRF = myrobot.getIRRF();
    unsigned char IRRB = myrobot.getIRRB();
    this->ui->lcdNumber_2->display(IRLF);
    this->ui->lcdNumber_4->display(IRRF);
    this->ui->lcdNumber_5->display(IRLB);
    this->ui->lcdNumber_6->display(IRRB);

}

void MainWindow::batterie(){
    this->ui->progressBar->setValue((myrobot.getBat()/205)*100);
}

void MainWindow::on_pushButton_2_pressed()//Pressage du bouton "Haut"
{
    myrobot.move_forward();
    batterie();
    odometrie();
    vitesse();
    infrarouge();

}
void MainWindow::on_pushButton_2_released()//Relâchage du bouton "Haut"
{
    myrobot.stop();
    batterie();
    odometrie();
    vitesse();
    infrarouge();
}

void MainWindow::on_pushButton_3_pressed()//Pressage du bouton "Droite"
{
    myrobot.turn_right();
    batterie();
    odometrie();
    vitesse();
    infrarouge();
}
void MainWindow::on_pushButton_3_released()//Relâchage du bouton "Droite"
{
    myrobot.stop();
    batterie();
    odometrie();
    vitesse();
    infrarouge();
}

void MainWindow::on_pushButton_4_pressed()//Pressage du bouton "Bas"
{
    myrobot.move_backward();
    batterie();
    odometrie();
    vitesse();
    infrarouge();
}
void MainWindow::on_pushButton_4_released()//Relâchage du bouton "Bas"
{
    myrobot.stop();
    batterie();
    odometrie();
    vitesse();
    infrarouge();
}

void MainWindow::on_pushButton_pressed()//Pressage du bouton "Gauche"
{
    myrobot.turn_left();
    batterie();
    odometrie();
    vitesse();
    infrarouge();

}
void MainWindow::on_pushButton_released()//Relâchage du bouton "Gauche"
{
    myrobot.stop();
    batterie();
    odometrie();
    vitesse();
    infrarouge();
}

void MainWindow::on_pushButton_5_clicked() //Bouton connexion
{
    myrobot.doConnect();
    batterie();
    odometrie();
    vitesse();
    infrarouge();

}

void MainWindow::on_pushButton_6_clicked() //Bouton deconnexion
{
    myrobot.disConnect();
    this->ui->progressBar->setValue(0);
    this->ui->lcdNumber->display(0);
    this->ui->lcdNumber_2->display(0);

}

