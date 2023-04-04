#include <QJsonDocument>
#include <QJsonObject>
#include <memory>
#include "../include/ClientCore.hpp"
#include "../include/Processor/AuthUserProcessor.hpp"
#include "../include/Processor/CreateUserProcessor.hpp"
#include "qtcpsocket.h"


ClientCore::ClientCore(QTcpSocket* socket, quint64 socketId): socket(socket), socketId(socketId)
{
//    this->socket = std::make_shared<QTcpSocket>(socket);

    connect(
        socket, &QTcpSocket::readyRead,
        this, &ClientCore::slotReadData
    );

    connect(
        socket, &QTcpSocket::disconnected,
        this, &ClientCore::slotDisconnect
    );
}

ClientCore::~ClientCore()
{
    qDebug("Deleting user object %llo", socketId);
    slotDisconnect();
}

QTcpSocket* ClientCore::getSocket()
{
    return socket;
}

quint64 ClientCore::getSocketId()
{
    return socketId;
}

void ClientCore::slotReadData()
{
    QByteArray request;

    while(socket->bytesAvailable() > 0) {
        request = socket->readAll();
    }

    if (request.size() == 0) {
        return;
    }

    if (request == "q") {
        socket->write("\nGood by!\n");
        slotDisconnect();

        return;
    } else {

    }

    QJsonDocument rq = QJsonDocument::fromJson(request);
    if (!rq.isObject()) {
        socket->write("Invalid request\n");

        return;
    }
    QJsonObject rqObject = rq.object();

    switch (rqObject["method"].toInt()) {
        case CreateUserProcessor::AUTH_METHOD:
            CreateUserProcessor::process(rqObject["params"], this);
            break;
        case AuthUserProcessor::AUTH_METHOD:
            AuthUserProcessor::process(rqObject["params"], this);
            break;
        default:
            socket->write("\nInvalid request\n");
            break;
    }
}

void ClientCore::slotDisconnect()
{
    if (state == 0) {
        state = 1;
        emit signalClientClose(socketId);

        socket->close();
    }
}
