#include "mainwindow.h"

#include <QApplication>
#include <QtCore/QTextStream>

QString decimalToHexadecimal(int number){
    QString hexNum = QString::number(number, 16);
    return hexNum;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int decimalNum = 120;
    QString hexNum = decimalToHexadecimal(decimalNum);

    return a.exec();
}
