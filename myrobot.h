#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QThread>

struct Data{
    int SpeedFront;
    unsigned char BatLevel;
    int IR;
    unsigned char IR2;
    float odometry;
    unsigned char Current;
    unsigned char Version;
};

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    //déclaration de la fonction pour le calcul de CRC
    short Crc16(char *Adresse_tab, unsigned char Taille_max);
    //déclaration des fonctions pour déplacer le robot
    void move_forward();
    void move_backward();
    void turn_left();
    void turn_right();
    void stop();
    /*int augmenterVitesse();
    int diminuerVitesse();*/

    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
    Data dataL = {};
    Data dataR= {};
    void info();

    int getIR();
    unsigned char getBat();
    unsigned char getCurrent();
    float getSpeed();
    float getOdometry();

    QByteArray getData();


signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;   
};

#endif // MYROBOT_H
