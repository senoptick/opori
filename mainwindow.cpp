#include "mainwindow.h"
#include "plc_network.h"
#include "./ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    plc = PlcNetwork::instance();

    connect(plc, &PlcNetwork::dataReceived,
            this, &MainWindow::onPlcDataReceived);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        // Получаем текущее время
        QDateTime time = QDateTime::currentDateTime();

        // Форматируем часы, минуты и секунды
        QString textTime = time.toString("hh:mm:ss");
        QString textDate = time.toString("dd.MM.yyyy");
        // Выводим в QLabel
        ui->lbl_CurrentTime->setText(textTime);
        ui->lbl_CurrentDate->setText(textDate);
    });

    // Запускаем таймер с интервалом в 1 секунду (1000 мс)
    timer->start(1000);
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

