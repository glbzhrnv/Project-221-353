#include <memory>
#include <QJsonDocument>
#include <QJsonObject>
#include "Enum/RequestMethod.hpp"
#include "Model/UserStateModel.hpp"
#include "Transport.hpp"

UserStateModel::UserStateModel(QObject* parent): QObject(parent)
{
}

void UserStateModel::setSocket(QTcpSocket* socket)
{
    connect(
        socket, &QTcpSocket::disconnected,
        this, &UserStateModel::onDisconnected
    );
}

UserStateModel::~UserStateModel()
{
}

bool UserStateModel::isLoggedIn()
{
    return state == 1;
}

QJsonObject UserStateModel::reg(std::string login, std::string password)
{
    QJsonObject params = {
        {"login", login.c_str()},
        {"password", password.c_str()}
    };

    socket->sendRequest(ENUM::LOGIN, &params);

    QJsonObject response = socket->readResponse();

    if (response["code"].toInt(-1) == 0) {
        emit registered(&response);

        state = 1;
        socket->setToken(response["result"].toObject()["token"].toString().toStdString());
    }

    return response;
}

QJsonObject UserStateModel::login(std::string login, std::string password)
{
    QJsonObject params = {
        {"login", login.c_str()},
        {"password", password.c_str()}
    };

    socket->sendRequest(ENUM::REG, &params);

    QJsonObject response = socket->readResponse();

    if (response["code"].toInt(-1) == 0) {
        emit loggedIn(&response);

        state = 1;
        socket->setToken(response["result"].toObject()["token"].toString().toStdString());
    }

    return response;
}

bool UserStateModel::logout()
{
    socket->sendRequest(ENUM::LOGOUT);

    QJsonObject response = socket->readResponse();

    if (response["code"].toInt(-1) == 0) {
        emit loggedOut(&response);

        userData = {};

        return true;
    }

    return false;
}

QJsonObject UserStateModel::getTask(ENUM::FSMType type)
{
    QJsonObject result = {
        {"type", type},
    };

    socket->sendRequest(ENUM::GET_TASK, &result);

    return socket->readResponse();
}

QJsonObject UserStateModel::sendTask(int32_t taskId, QString answer)
{
    QJsonObject result = {
        {"task_id", taskId},
        {"answer", answer}
    };

    socket->sendRequest(ENUM::SEND_TASK, &result);

    emit taskComplete();

    return socket->readResponse();
}

QJsonObject UserStateModel::getStat(ENUM::StatType type)
{
    QJsonObject result = {
        {"type", type},
    };

    socket->sendRequest(ENUM::GET_TASK, &result);

    return socket->readResponse();
}

void UserStateModel::onDisconnected()
{
    userData = {};
}
