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
    m_buffer.append(data);

    while (m_buffer.size() >= 5) // минимальный пакет
    {
        // ищем начало пакета
        int start = m_buffer.indexOf(char(0xAA));
        if (start == -1) {
            m_buffer.clear();
            return;
        }

        if (start > 0)
            m_buffer.remove(0, start);

        if (m_buffer.size() < 5)
            return;

        quint8 type = (quint8)m_buffer[1];
        quint8 len  = (quint8)m_buffer[2];

        int packetSize = 1 + 1 + 1 + len + 1;

        if (m_buffer.size() < packetSize)
            return;

        // проверка конца пакета
        if ((quint8)m_buffer[packetSize - 1] != 0x55) {
            m_buffer.remove(0, 1); // сдвиг
            continue;
        }

        QByteArray payload = m_buffer.mid(3, len);

        QDataStream in(payload);
        in.setByteOrder(QDataStream::BigEndian);

        qint32 value;
        in >> value;

        // 👇 ОБРАБОТКА ТИПОВ
        switch (type)
        {
        case 1: // время цикла
            ui->lbl_CycleTime->setText(QString::number(value) + " ms");
            break;

        case 2: // количество заготовок
            ui->lbl_PartsCount->setText(QString::number(value));
            break;

        default:
            qDebug() << "Неизвестный тип:" << type;
            break;
        }

        // для отладки (hex)
        ui->lbl_CycleTime->setText(QString::fromUtf8(m_buffer.left(packetSize).toHex(' ')));

        m_buffer.remove(0, packetSize);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (!plc) return;

    QByteArray packet;
    packet.append(char(0xAA));
    packet.append(char(10)); // CmdStart
    packet.append(char(0));  // без данных
    packet.append(char(0x55));

    plc->sendCommand(packet);

    qDebug() << "START отправлен";
}


void MainWindow::on_pushButton_2_clicked()
{
    if (!plc) return;

    QByteArray packet;
    packet.append(char(0xAA));
    packet.append(char(11)); // CmdStop
    packet.append(char(0));
    packet.append(char(0x55));

    plc->sendCommand(packet);

    qDebug() << "STOP отправлен";
}

