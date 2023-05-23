// myrobot.cpp

#include "myrobot.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x00; //valeurs entre 0 et x78 pour gauche
    DataToSend[3] = 0x00; //valeurs entre 0 et x78 pour gauche
    DataToSend[4] = 0x00; //valeurs entre 0 et x78 pour droite
    DataToSend[5] = 0x00; //valeurs entre 0 et x78 pour droite
    DataToSend[6] = 0x00; //valeurs si on avance, recule
    DataToSend[7] = 0x00;
    DataToSend[8] = 0x00;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
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
    qDebug() << DataReceived[2] << DataReceived[3] << DataReceived[4];
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}


QByteArray MyRobot::getData(){
    return DataToSend;
}


//Création des fonctions pour déplacer le robot :
//Fonction pour avancer :
void MyRobot::move_forward(){
    //On met les roues à pleine vitesse
    DataToSend[2] = 120;
    DataToSend[3] = 120;
    DataToSend[4] = 120;
    DataToSend[5] = 120;
    DataToSend[6] = 80;//On dit au robot que les roues tourne dans le sens anti-horaire
    //calcul du CRC
    short crc = Crc16(DataToSend.data()+1,6);
    char bitFaible = crc & 0x00FF;
    char bitFort = (crc & 0xFF00) >> 8;
    DataToSend[7] = bitFaible;
    DataToSend[8] = bitFort;
}
//Fonction pour reculer
void MyRobot::move_backward(){
    //On met les roues à pleine vitesse
    DataToSend[2] = 120;
    DataToSend[3] = 120;
    DataToSend[4] = 120;
    DataToSend[5] = 120;
    DataToSend[6] = 00; //On dit au robot que les roues tourne dans le sens horaire
    //calcul du CRC
    short crc = Crc16(DataToSend.data()+1,6);
    char bitFaible = crc & 0x00FF;
    char bitFort = (crc & 0xFF00) >> 8;
    DataToSend[7] = bitFaible;
    DataToSend[8] = bitFort;
}
//Fonction pour tourner à gauche
void MyRobot::turn_left(){
    //On arrête les roues gauche et on met les roues droites à pleine vitesse
    DataToSend[2] = 0;
    DataToSend[3] = 0;
    DataToSend[4] = 120;
    DataToSend[5] = 120;
    DataToSend[6] = 80;
    //calcul du CRC
    short crc = Crc16(DataToSend.data()+1,6);
    char bitFaible = crc & 0x00FF;
    char bitFort = (crc & 0xFF00) >> 8;
    DataToSend[7] = bitFaible;
    DataToSend[8] = bitFort;
}
//Fonction pour tourner à droite
void MyRobot::turn_right(){
    //On arrête les roues droite et on mets les roues gauches à pleine vitesse
    DataToSend[2] = 120;
    DataToSend[3] = 120;
    DataToSend[4] = 0;
    DataToSend[5] = 0;
    DataToSend[6] = 80;
    //calcul du CRC
    short crc = Crc16(DataToSend.data()+1,6);
    char bitFaible = crc & 0x00FF;
    char bitFort = (crc & 0xFF00) >> 8;
    DataToSend[7] = bitFaible;
    DataToSend[8] = bitFort;
}
//Fonction pour arrêter le robot
void MyRobot::stop(){
    //On arrête toutes les roues
    DataToSend[2] = 0;
    DataToSend[3] = 0;
    DataToSend[4] = 0;
    DataToSend[5] = 0;
    DataToSend[6] = 0;

    short crc = Crc16(DataToSend.data()+1,6);
    char bitFaible = crc & 0x00FF;
    char bitFort = (crc & 0xFF00) >> 8;
    DataToSend[7] = bitFaible;
    DataToSend[8] = bitFort;
}

//Fonction pour calculer le CRC
short MyRobot::Crc16(char *Adresse_tab, unsigned char Taille_max){
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity= 0;
    Crc = 0xFFFF;
    Polynome = 0xA001;
    for ( CptOctet= 0 ; CptOctet < Taille_max ; CptOctet++)
    {
        Crc ^= *( Adresse_tab + CptOctet);
        for ( CptBit = 0; CptBit <= 7 ; CptBit++)
        {
            Parity= Crc;
            Crc >>= 1;
            if (Parity%2 == true) Crc ^= Polynome;
        }
    }
    return(Crc);
}

