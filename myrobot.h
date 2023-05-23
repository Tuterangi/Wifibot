#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>


struct Data{
    float SpeedFront;
    float BatLevel;
    float IR;
    float IR2;
    float odometry;
    float Current;
    float Version;
};




class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;

    Data dataL = {};
    Data dataR= {};
    void info();

    float getIR();
    float getBat();
    float getCurrent();
    float getSpeed();
    float getOdometry();



    //QByteArray *dataL;
    //QByteArray *dataR;


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
