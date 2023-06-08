#ifndef TRANSPORT_CPP
#define TRANSPORT_CPP

#include <string>
#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include "Enum/RequestMethod.hpp"
#include "qtcpsocket.h"

class Transport
{
public:
    Transport(QObject *parent = nullptr)
    {
        socket = new QTcpSocket(parent);
        socket->connectToHost("127.0.0.1", 33333);

        if (socket->waitForConnected(1000)) {
            qDebug() << "Connected!";
            socket->waitForReadyRead(1000);
            socket->readAll();
        } else {
            qDebug() << "no Connected!";
        }
    }

    ~Transport()
    {
    }

    static std::string  createRequest(
        ENUM::RequestMethod method,
        QJsonObject* params = nullptr
    ) {
        QJsonObject result = {
            {"method", method}
        };

        if (params != nullptr) {
            result["params"] = *params;
        }

        return QJsonDocument(result).toJson(QJsonDocument::Compact).toStdString();
    }

    bool sendRequest(ENUM::RequestMethod method, QJsonObject* params = nullptr)
    {
        QJsonObject localParams = {};
//        if (params != nullptr) {
//            localParams = *params;
//        }

//        if (token != "") {
//            localParams["token"] = token.c_str();
//        }

        socket->state();
//        if (socket->state() == QTcpSocket::ConnectedState) {
//            return false;
//        }

        std::string request = createRequest(method, params);

        qDebug() << "Request: " << request.c_str();

        socket->write(request.c_str(), request.size());

        return true;
    }

    QJsonObject readResponse()
    {
        socket->waitForReadyRead();

        QByteArray result = socket->readAll();

        qDebug() << "Response: " << result;

        QJsonDocument rq = QJsonDocument::fromJson(result);

        return rq.object();
    }

    void setToken(std::string token)
    {
        this->token = token;
    }

    QTcpSocket* getSocket()
    {
        return socket;
    }

protected:
    QTcpSocket *socket;
    std::string token = "";
};

#endif // TRANSPORT_CPP
