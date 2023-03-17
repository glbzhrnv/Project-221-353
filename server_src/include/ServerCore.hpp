#ifndef SERVER_CORE_HPP
#define SERVER_CORE_HPP

#include <map>
#include <QtGlobal>
#include <QRandomGenerator>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

#include "ClientCore.hpp"

class ServerCore : public QObject
{
    Q_OBJECT
public slots:
    void slotAddConnection();
    void slotDeleteConnection(quint64 id);

public:
    explicit ServerCore(QObject *parent = nullptr);
    ~ServerCore();

protected:
    QTcpServer* mTcpServer;
    std::map<quint64, ClientCore*> clientsMap;
};
#endif // SERVER_CORE_HPP







