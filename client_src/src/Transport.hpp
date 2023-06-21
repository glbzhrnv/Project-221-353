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

/**
 * @brief Организует приёмопередачу данных с сервером
 */
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

    /**
     * @brief Оформляет передаваеммые к серверу, данные
     * @param method - Идентификатор метода
     * @param params - Передаваемые данные
     * @return
     */
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

    /**
     * @brief Возвращает экземпляр сокета
     * @return Указатель на сокет
     */
    QTcpSocket* getSocket()
    {
        return socket;
    }

    /**
     * @brief Отправляет данные на сервер
     * @param method - Идентификатор метода
     * @param params - Передаваемые данные
     * @return Статус передачи
     */
    bool sendRequest(ENUM::RequestMethod method, QJsonObject* params = nullptr)
    {
        if (socket->state() != QTcpSocket::ConnectedState) {
            return false;
        }

        std::string request = createRequest(method, params);

        qDebug() << "Request: " << request.c_str();

        socket->write(request.c_str(), request.size());

        return true;
    }

    /**
     * @brief Получает данные, переданные сервером
     * @return Ответ сервера
     */
    QJsonObject readResponse()
    {
        socket->waitForReadyRead();

        QByteArray result = socket->readAll();

        qDebug() << "Response: " << result;

        QJsonDocument rq = QJsonDocument::fromJson(result);

        return rq.object();
    }

protected:
    QTcpSocket *socket;
};

#endif // TRANSPORT_CPP
