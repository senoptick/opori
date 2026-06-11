#include "mainwindow.h"
#include "plc_network.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    plc = PlcNetwork::instance();

    connect(plc, &PlcNetwork::dataReceived,
            this, &MainWindow::onPlcDataReceived);
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

void MainWindow::onPlcDataReceived(const QByteArray &data)
{
    ui->lbl1->setText(QString::fromUtf8(data.toHex(' ')));
}

void MainWindow::on_pushButton_2_clicked()
{
    if (!plc) return;

    QByteArray packet;
    packet.append(2);
    plc->sendCommand(packet);

    qDebug() << "Отправлено на PLC →" << packet.trimmed();
}

