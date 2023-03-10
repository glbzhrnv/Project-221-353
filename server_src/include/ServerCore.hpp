#ifndef SERVER_CORE_HPP
#define SERVER_CORE_HPP

#include <vector>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class ServerCore : public QObject
{
    Q_OBJECT
public slots:
    void slotNewConnection();
    void slotClientDisconnected();

    void slotServerRead();

signals:
    void signalRegisterConnection();

public:
    explicit ServerCore(QObject *parent = nullptr);
    ~ServerCore();

protected:
    QTcpServer* mTcpServer;
    std::vector<QTcpSocket*>  clientSocketsVec;
    int state = 0;
};
#endif // SERVER_CORE_HPP







