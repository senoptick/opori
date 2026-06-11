#include "mainwindow.h"
#include "plc_network.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    plc = PlcNetwork::instance();

    connect(plc, &PlcNetwork::cycleTimeUpdated,
            this, [this](double value) {
                ui->lcdNumber->display(value);
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    if (!plc) return;

    QByteArray packet;
    packet.append(1);
    plc->sendCommand(packet);

    qDebug() << "Отправлено на PLC →" << packet.trimmed();
}


void MainWindow::on_pushButton_2_clicked()
{
    if (!plc) return;

    QByteArray packet;
    packet.append(2);
    plc->sendCommand(packet);

    qDebug() << "Отправлено на PLC →" << packet.trimmed();
}

