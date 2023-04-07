#include <memory>
#include <QDebug>
#include <QRandomGenerator>
#include <QTcpServer>
#include "Exception/ConfigurationException.hpp"
#include "Exception/ConnectionException.hpp"
#include "ServerCore.hpp"
#include "SharedObjects.hpp"

ServerCore::ServerCore(QObject *parent): QObject(parent)
{
}

ServerCore::~ServerCore()
{
    mTcpServer->close();
}

void ServerCore::setupSocket()
{
    mTcpServer = new QTcpServer(this);

    QJsonObject settings = SharedObjects::getPointer()->getSettings();
    QJsonValue port = settings["server_port"];

    if (!port.isDouble()) {
        throw new ConfigurationException("'server_port' must be a number");
    }

    if (!mTcpServer->listen(QHostAddress::Any, port.toInt())) {
        throw new ConnectionException("Unable to open server socket");
    }

    connect(
        mTcpServer, &QTcpServer::newConnection,
        this, &ServerCore::slotAddConnection
    );
}

void ServerCore::slotAddConnection()
{
    quint64 socketId = QRandomGenerator::system()->generate64();
    std::unique_ptr<ClientCore> clientData = std::make_unique<ClientCore>(
        mTcpServer->nextPendingConnection(),
        socketId
    );

    connect(
        clientData.get(), &ClientCore::signalClientClose,
        this, &ServerCore::slotDeleteConnection
    );

    clientsMap[socketId] = std::move(clientData);

    qDebug("Client connected");
}

void ServerCore::slotDeleteConnection(quint64 id)
{
    if (clientsMap.count(id) != 0) {
        qDebug("Deleting socket");

        clientsMap.erase(id);
    }
}
