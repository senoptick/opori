#ifndef PLC_NETWORK_H
#define PLC_NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>

class PlcNetwork : public QObject
{
    Q_OBJECT

public:
    //singleton
    static PlcNetwork* instance();

    void connectToPlc(const QString &host, quint16 port);
    void changeConnection(const QString &host, quint16 port);
    void sendCommand(const QByteArray &data);
    void disconnectFromPlc();

signals:
    void connected();
    void disconnected();
    void dataReceived(const QByteArray &data);
    void errorOccurred(const QString &error);
    void statusChanged(const QString &status);

private:
    explicit PlcNetwork(QObject *parent = nullptr);
    ~PlcNetwork();

    Q_DISABLE_COPY(PlcNetwork)

    static PlcNetwork* m_instance;

    QTcpSocket *m_socket = nullptr;

    //default
    QString m_host = "192.168.58.88";
    quint16 m_port = 1000;

private slots:
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketReadyRead();
    void onSocketError(QAbstractSocket::SocketError socketError);
};

#endif // PLC_NETWORK_H
