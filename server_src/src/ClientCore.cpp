#include "../include/ClientCore.hpp"
#include "qtcpsocket.h"

ClientCore::ClientCore(QTcpSocket* socket, quint64 socketId): socket(socket), socketId(socketId)
{
    connect(
        socket, &QTcpSocket::readyRead,
        this, &ClientCore::slotReadData
    );

    connect(
        socket, &QTcpSocket::disconnected,
        this, &ClientCore::slotDisconnect
    );

    socket->write("Hello, World!!! I am echo server!\n");
}

ClientCore::~ClientCore()
{
    qDebug() << "Deleting user object" << socketId;
    slotDisconnect();
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
    } else {
        socket->write(request); // echo
//        socket->write("Invalid request\n");
    }

    qDebug() << request;
}

void ClientCore::slotDisconnect()
{
    if (state == 0) {
        state = 1;
        emit signalClientClose(socketId);

        socket->close();

        deleteLater();
    }
}
