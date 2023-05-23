#include "myrobot.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , bot(parent)

{
    ui->setupUi(this);
    bot.doConnect();
    bot.info();
    bot.getIR();
    //bot.readyRead();


}

MainWindow::~MainWindow()
{
    delete ui;
    bot.disConnect();


}



void MainWindow::on_pushButton_clicked()
{

}

