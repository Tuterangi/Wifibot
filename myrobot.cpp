// myrobot.cpp

#include "myrobot.h"
#include "qwebengineview.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    //manager=new QNetworkAccessManager();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
    info();
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

void MyRobot::info(){
    dataL.SpeedFront=(int)((DataReceived[1] << 8) + DataReceived[0]);
    if (dataL.SpeedFront > 32767) dataL.SpeedFront=dataL.SpeedFront-65536;
    dataL.BatLevel=DataReceived[2];
    dataL.IR=DataReceived[3];
    dataL.IR2=DataReceived[4];
    dataL.odometry=((((long)DataReceived[8] << 24))+(((long)DataReceived[7] <<16))+(((long)DataReceived[6] << 8))+((long)DataReceived[5]));
    dataR.SpeedFront=(int)(DataReceived[10] << 8) + DataReceived[9];
    if (dataR.SpeedFront > 32767) dataR.SpeedFront=dataR.SpeedFront-65536;
    dataR.BatLevel=0;
    dataR.IR=DataReceived[11];
    dataR.IR2=DataReceived[12];
    dataR.odometry=((((long)DataReceived[16] << 24))+(((long)DataReceived[15] <<16))+(((long)DataReceived[14] << 8))+((long)DataReceived[13]));
    dataL.Current=DataReceived[17];
    dataR.Current=DataReceived[17];
    dataL.Version=DataReceived[18];
    dataR.Version=DataReceived[18];

    qDebug() << "info : " << dataL.IR;
}

float MyRobot::getIR(){
    return(dataL.IR);
}

float MyRobot::getBat(){
    return(dataL.BatLevel);
}
float MyRobot::getCurrent(){
    return(dataL.Current);
}
float MyRobot::getSpeed(){
    return(dataL.SpeedFront);
}
float MyRobot::getOdometry(){
    return(dataL.odometry);
}

/*void MyRobot::camRight(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
}

void MyRobot::camLeft(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
}

void MyRobot::camUp(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
}

void MyRobot::camDown(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
}*/

