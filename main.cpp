#include "myclient.h"
#include <QApplication>


void f(){
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    qDebug() << list[2].toString();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyClient client("192.168.0.141",2323);
    f();
    client.show();

    return a.exec();
}
