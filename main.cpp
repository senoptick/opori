#include "mainwindow.h"

#include "plc_network.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PlcNetwork *plc = PlcNetwork::instance();
    plc -> connectToPlc("192.168.58.88", 1000);
    MainWindow w;
    w.show();
    return a.exec();
}
