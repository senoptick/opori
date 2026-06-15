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




void MainWindow::onPlcDataReceived(const QByteArray &data)
{
    if (data.size() < 9) {
        qDebug() << "Bad packet size:" << data.size();
        return;
    }

    quint8 cmd = static_cast<quint8>(data[0]);

    if (cmd == 5) { // telemetry
        quint32 cycleTime = 0;
        quint32 partsCount = 0;

        memcpy(&cycleTime, data.constData() + 1, 4);
        memcpy(&partsCount, data.constData() + 5, 4);

        // если PLC little-endian — ок
        // если big-endian — нужно qFromBigEndian

        ui->lbl_CycleTime->setText(QString::number(cycleTime) + " ms");
        ui->lbl_PartsCount->setText(QString::number(partsCount));
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (!plc) return;
    QByteArray packet;
    packet.append(char(0x01));
    plc->sendCommand(packet);

    qDebug() << "Отправлено на PLC →" << packet.trimmed();
}


void MainWindow::on_pushButton_2_clicked()
{
    if (!plc) return;
    QByteArray packet;
    packet.append(char(0x02));
    plc->sendCommand(packet);

    qDebug() << "Отправлено на PLC →" << packet.trimmed();
}

