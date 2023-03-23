#include "../include/ServerCore.hpp"

ServerCore::ServerCore(QObject *parent): QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server setup failed";

        return;
    }

    connect(
        mTcpServer, &QTcpServer::newConnection,
        this, &ServerCore::slotAddConnection
    );

    qDebug() << "Server is setted up";
}

ServerCore::~ServerCore()
{
    mTcpServer->close();
}

void ServerCore::slotAddConnection()
{
    quint64 socketId = QRandomGenerator::system()->generate64();
    ClientCore* clientData = new ClientCore(
        mTcpServer->nextPendingConnection(),
        socketId
    );

    connect(
        clientData, &ClientCore::signalClientClose,
        this, &ServerCore::slotDeleteConnection
    );

    clientsMap[socketId] = clientData;

    qDebug() << "Client connected";
}

void ServerCore::slotDeleteConnection(quint64 id)
{
    if (clientsMap.count(id) != 0) {
        qDebug() << "Deleting socket";

        clientsMap.erase(id);
    }
}
