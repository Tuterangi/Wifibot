#include "myrobot.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , bot(parent)

{
    ui->setupUi(this);
    bot.doConnect();
    bot.info();
    bot.getIR();
    QWebEngineView *video= new QWebEngineView();
    manager=new QNetworkAccessManager();

    //bot.readyRead();
    //QNetworkAccessManager *manager=new QNetworkAccessManager();
    printVideo(video);



}

MainWindow::~MainWindow()
{
    delete ui;
    bot.disConnect();


}





void MainWindow::printVideo(QWebEngineView *video){
    video->setGeometry(0,0,351,301);
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




void MainWindow::on_right_clicked()
{
    camRight();
}


void MainWindow::on_Up_clicked()
{
    camUp();
}


void MainWindow::on_Left_clicked()
{
    camLeft();
}


void MainWindow::on_Down_clicked()
{
    camDown();
}

