#include "mainwindow.h"

#include "plc_network.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, true);
    QApplication a(argc, argv);

    PlcNetwork *plc = PlcNetwork::instance();
    plc -> connectToPlc("169.254.37.12", 1000);
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
