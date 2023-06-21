#include <QJsonDocument>
#include <QJsonObject>
#include "Processor/AbstractProcessor.hpp"
#include "Processor/AuthUserProcessor.hpp"
#include "Processor/CreateUserProcessor.hpp"
#include "Processor/GetStatProcessor.hpp"
#include "Processor/GetTaskProcessor.hpp"
#include "Processor/SendTaskProcessor.hpp"
#include "ClientCore.hpp"

ClientCore::ClientCore(QTcpSocket *socket, quint64 socketId): socket(socket), socketId(socketId)
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

Model::UserStateModel* ClientCore::userStateGet()
{
    return &userState;
}

void ClientCore::slotReadData()
{
    QByteArray request, result;

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
        slotDisconnect();

        return;
    }

    result = AbstractProcessor::createResponse(-2);
    QJsonDocument rq = QJsonDocument::fromJson(request);
    if (rq.isObject()) {
        QJsonObject
            requestObject = rq.object(),
            params = requestObject["params"].toObject();

        switch (requestObject["method"].toInt()) {
        case CreateUserProcessor::METHOD_ID:
            result = CreateUserProcessor().process(params, this);
            break;
        case AuthUserProcessor::METHOD_ID:
            result = AuthUserProcessor().process(params, this);
            break;
        case GetTaskProcessor::METHOD_ID:
            result = GetTaskProcessor().process(params, this);
            break;
        case SendTaskProcessor::METHOD_ID:
            result = SendTaskProcessor().process(params, this);
            break;
        case GetStatProcessor::METHOD_ID:
            result = GetStatProcessor().process(params, this);
            break;
        }
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
