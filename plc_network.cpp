#include "plc_network.h"
#include <QDebug>
#include <QTimer>

PlcNetwork* PlcNetwork::m_instance = nullptr;

PlcNetwork* PlcNetwork::instance()
{
    if (!m_instance) {
        m_instance = new PlcNetwork();
    }
    return m_instance;
}

PlcNetwork::PlcNetwork(QObject *parent)
    : QObject(parent)
{
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &PlcNetwork::onSocketConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &PlcNetwork::onSocketDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &PlcNetwork::onSocketReadyRead);
    connect(m_socket, &QTcpSocket::errorOccurred, this, &PlcNetwork::onSocketError);
}

PlcNetwork::~PlcNetwork()
{
    disconnectFromPlc();
    m_instance = nullptr;
}

void PlcNetwork::connectToPlc(const QString &host, quint16 port)
{
    m_host = host;
    m_port = port;
    qDebug() << "PlcNetwork: Подключение к" << host << ":" << port;
    m_socket->connectToHost(host, port);
}

void PlcNetwork::changeConnection(const QString &host, quint16 port)
{
    qDebug() << "PlcNetwork: Смена соединения на" << host << ":" << port;
    disconnectFromPlc();
    connectToPlc(host, port);
}

void PlcNetwork::disconnectFromPlc()
{
    if (m_socket && m_socket->state() != QAbstractSocket::UnconnectedState) {
        m_socket->disconnectFromHost();
        m_socket->waitForDisconnected(1000);  // опционально, чтобы дождаться
    }
}

void PlcNetwork::sendCommand(const QByteArray &data)
{
    if (m_socket && m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write(data);
        m_socket->flush();
        qDebug() << "PlcNetwork: Отправлено:" << data;
    } else {
        qDebug() << "PlcNetwork: Не подключено — команда не отправлена:" << data;
    }
}

void PlcNetwork::onSocketConnected()
{
    qDebug() << "PlcNetwork: Подключено к PLC!";

    // TODO: Отправлть инициализационную команду сразу
    //sendCommand("HELLO\r\n");

    QByteArray packet;
    packet.append(2);
    packet.append(char(0));
    packet.append(char(0));

    sendCommand(packet);

    // emit connected();
    // emit statusChanged("Подключено");
}

void PlcNetwork::onSocketDisconnected()
{
    qDebug() << "PlcNetwork: Отключено от PLC";
    emit disconnected();
    emit statusChanged("Отключено");

    // Автоматическое переподключение
    // QTimer::singleShot(5000, this, [this]() {
    //     qDebug() << "PlcNetwork: Попытка переподключения...";
    //     m_socket->connectToHost(m_host, m_port);
    // });
}

void PlcNetwork::onSocketReadyRead()
{
    QByteArray data = m_socket->readAll();
    qDebug() << "PlcNetwork: Получено:" << data.toHex();

    if (data.size() >= 4) {
        float cycleTime;
        memcpy(&cycleTime, data.constData(), sizeof(float));

        emit cycleTimeUpdated(static_cast<double>(cycleTime));
    }
}

void PlcNetwork::onSocketError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    QString err = m_socket ? m_socket->errorString() : "Сокет не инициализирован";
    qDebug() << "PlcNetwork: Ошибка сокета:" << err;
    emit errorOccurred(err);
    emit statusChanged("Ошибка: " + err);
}
