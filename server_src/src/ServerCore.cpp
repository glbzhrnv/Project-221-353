#include "../include/ServerCore.hpp"
#include <QDebug>
#include <QCoreApplication>

ServerCore::ServerCore(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(
        mTcpServer, &QTcpServer::newConnection,
        this, &ServerCore::slotNewConnection
    );

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server setup failed";
    } else {
        state = 1;
        qDebug() << "Server is setted up";
    }
}

ServerCore::~ServerCore()
{
    mTcpServer->close();
    state = 0;
}

void ServerCore::slotNewConnection()
{
    if (state == 1) {
        QTcpSocket* clientSocket = mTcpServer->nextPendingConnection();
        clientSocketsVec.push_back(clientSocket);

        connect(
            clientSocket, &QTcpSocket::readyRead,
            this,&ServerCore::slotServerRead
        );
        connect(
            clientSocket, &QTcpSocket::disconnected,
            this, &ServerCore::slotClientDisconnected
        );
        clientSocket->write("Hello, World!!! I am echo server!\n");

        qDebug() << "Client connected";
    }
}

void ServerCore::slotServerRead()
{
    QByteArray request;

    while(mTcpSocket->bytesAvailable() > 0) {
        request = mTcpSocket->readAll();
    }

    if (request.size() == 0) {
        return;
    }

    if (request == "quit") {
        mTcpSocket->write("Good by!\n");
        mTcpSocket->close();
    } else {
        mTcpSocket->write("Invalid request\n");
    }

    qDebug() << request;
}

void ServerCore::slotClientDisconnected(){
    mTcpSocket->close();
}
