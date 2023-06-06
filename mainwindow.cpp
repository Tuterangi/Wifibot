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
    //bot.readyRead();

    printVideo(video);


}

MainWindow::~MainWindow()
{
    delete ui;
    bot.disConnect();


}



void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::printVideo(QWebEngineView *video){
    video->setGeometry(0,0,351,301);
    QUrl url = QUrl("http://192.168.1.106:8080/?action=stream");
    video->load(url);
    video->setParent(ui->videoWidget);
    video->show();
}





