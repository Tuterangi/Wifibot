#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

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

    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;

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
