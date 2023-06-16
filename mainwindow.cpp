#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , myrobot(parent)

{
    ui->setupUi(this);
    myrobot.info();
    batterie();

    QWebEngineView *video= new QWebEngineView();
    manager=new QNetworkAccessManager();
    printVideo(video);

}

MainWindow::~MainWindow()
{
    delete ui;
}
//ajout du mouvement lorsque l'on presse le bouton ou non

void MainWindow::odometrie(){
    QString OL = QString::number(myrobot.getOdometryL()); //On récupère la position de la roue Gauche
    QString OR = QString::number(myrobot.getOdometryR()); //On récupère la position de la roue Droite
    this->ui->odometrie_gauche->setText((QString) OL); //On affiche la position de la roue Gauche
    this->ui->odometrie_droite->setText((QString) OR); //On affiche la position de la roue Droite
}

void MainWindow::vitesse(){
    long odometrie_diffL = myrobot.getOdometryL() - myrobot.getLastOdometryL();
    long odometrie_diffR = myrobot.getOdometryR() - myrobot.getLastOdometryR();
    int nb_tics = 2048;
    float temps = 0.075;
    float perimetre = 0.44;
    float VL = ((odometrie_diffL * perimetre)/nb_tics)/temps;
    float VR = ((odometrie_diffR * perimetre)/nb_tics)/temps;
    this->ui->vitesse_roue_gauche->display(VL);
    this->ui->vitesse_roue_droite->display(VR);
    qDebug() << "odometrie : " << (myrobot.getOdometryL()-myrobot.getLastOdometryL());
}

void MainWindow::infrarouge(){
    unsigned char IRLF = myrobot.getIRLF();
    unsigned char IRLB = myrobot.getIRLB();
    unsigned char IRRF = myrobot.getIRRF();
    unsigned char IRRB = myrobot.getIRRB();
    this->ui->capteur_avant_gauche->display(IRLF);
    this->ui->capteur_avant_droite->display(IRRF);
    this->ui->capteur_arriere_gauche->display(IRLB);
    this->ui->capteur_arriere_droite->display(IRRB);

}

void MainWindow::batterie(){
    this->ui->batterie->setValue(myrobot.getBat());
}

void MainWindow::printVideo(QWebEngineView *video){
    video->setGeometry(10,10,500,421);
    QUrl url = QUrl("http://192.168.1.106:8080/?action=stream");
    video->load(url);
    video->setParent(ui->videoWidget);
    video->show();
}

void MainWindow::camRight(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
}

void MainWindow::camLeft(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
}

void MainWindow::camUp(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
}

void MainWindow::camDown(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
}

void MainWindow::on_pushButton_2_pressed()//Pressage du bouton "Haut"
{
    myrobot.move_forward();
    //batterie();
    odometrie();
    vitesse();
    infrarouge();

}
void MainWindow::on_pushButton_2_released()//Relâchage du bouton "Haut"
{
    myrobot.stop();
    //batterie();
    odometrie();
    vitesse();
    infrarouge();
}

void MainWindow::on_pushButton_3_pressed()//Pressage du bouton "Droite"
{
    myrobot.turn_right();
   // batterie();
    odometrie();
    vitesse();
    infrarouge();
}
void MainWindow::on_pushButton_3_released()//Relâchage du bouton "Droite"
{
    myrobot.stop();
    //batterie();
    odometrie();
    vitesse();
    infrarouge();
}

void MainWindow::on_pushButton_4_pressed()//Pressage du bouton "Bas"
{
    myrobot.move_backward();
    //batterie();
    odometrie();
    vitesse();
    infrarouge();
}
void MainWindow::on_pushButton_4_released()//Relâchage du bouton "Bas"
{
    myrobot.stop();
    //batterie();
    odometrie();
    vitesse();
    infrarouge();
}

void MainWindow::on_pushButton_pressed()//Pressage du bouton "Gauche"
{
    myrobot.turn_left();
    //batterie();
    odometrie();
    vitesse();
    infrarouge();

}
void MainWindow::on_pushButton_released()//Relâchage du bouton "Gauche"
{
    myrobot.stop();
    //batterie();
    odometrie();
    vitesse();
    infrarouge();
}

void MainWindow::on_pushButton_5_clicked() //Bouton connexion
{
    myrobot.doConnect();
    //batterie();
    odometrie();
    vitesse();
    infrarouge();

}

void MainWindow::on_pushButton_6_clicked() //Bouton deconnexion
{
    myrobot.disConnect();
    /*this->ui->progressBar->setValue(0);
    this->ui->lcdNumber->display(0);
    this->ui->lcdNumber_2->display(0);*/

}


void MainWindow::on_Haut_clicked()
{
    camUp();
}


void MainWindow::on_Droite_clicked()
{
    camRight();
}


void MainWindow::on_Bas_clicked()
{
    camDown();
}


void MainWindow::on_Gauche_clicked()
{
    camLeft();
}


/*void MainWindow::on_Augmenter_clicked()
{
    myrobot.augmenter();
}


void MainWindow::on_diminuer_clicked()
{
    myrobot.diminuer();
}*/

