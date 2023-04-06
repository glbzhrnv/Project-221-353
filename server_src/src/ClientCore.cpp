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
        if (request.size() > REQUEST_MAX_SIZE) {
            break;
        }
        request = socket->read(REQUEST_MAX_SIZE);
    }

    if (request.size() == 0) {
        return;
    }

    if (request == "q") {
        socket->write("\nGood by!\n");
        slotDisconnect();

        return;
    }

    QJsonDocument rq = QJsonDocument::fromJson(request);
    if (!rq.isObject()) {
        socket->write("Invalid request\n");

        return;
    }
    QJsonObject
        requestObject = rq.object(),
        params = requestObject["params"].toObject();

    QByteArray result;
    switch (requestObject["method"].toInt()) {
        case CreateUser::METHOD_ID:
            result = CreateUser::Processor::process(params, this);
            break;
        case AuthUser::METHOD_ID:
            result = AuthUser::Processor::process(params, this);
            break;
        default:
            result = "\nInvalid request\n";
            break;
    }

    socket->write(result);
}

void ClientCore::slotDisconnect()
{
    if (state == 0) {
        state = 1;
        emit signalClientClose(socketId);

        socket->close();
    }
}
