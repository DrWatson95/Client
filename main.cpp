#include "myclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyClient client("192.168.0.141",2323);
    client.show();

    return a.exec();
}
