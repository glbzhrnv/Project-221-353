#include <memory>
#include <QJsonDocument>
#include <QJsonObject>
#include "Enum/RequestMethod.hpp"
#include "Model/UserStateModel.hpp"
#include "Transport.hpp"

UserStateModel::UserStateModel(QObject* parent): QObject(parent)
{
}

void UserStateModel::setTransport(Transport* transport)
{
    this->transport = transport;

    connect(
        transport->getSocket(), &QTcpSocket::disconnected,
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

    transport->sendRequest(ENUM::REG, &params);

    QJsonObject response = transport->readResponse();

    if (response["code"].toInt(-1) == 0) {
        emit registered(&response);

        state = 1;
    }

    return response;
}

QJsonObject UserStateModel::login(std::string login, std::string password)
{
    QJsonObject params = {
        {"login", login.c_str()},
        {"password", password.c_str()}
    };

    transport->sendRequest(ENUM::LOGIN, &params);

    QJsonObject response = transport->readResponse();

    if (response["code"].toInt(-1) == 0) {
        emit loggedIn(&response);

        state = 1;
    }

    return response;
}

bool UserStateModel::logout()
{
    transport->sendRequest(ENUM::LOGOUT);

    QJsonObject response = transport->readResponse();

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

    transport->sendRequest(ENUM::GET_TASK, &result);

    return transport->readResponse();
}

QJsonObject UserStateModel::sendTask(int32_t taskId, QString answer)
{
    QJsonObject result = {
        {"id", taskId},
        {"answer", answer}
    };

    transport->sendRequest(ENUM::SEND_TASK, &result);

    emit taskComplete();

    return transport->readResponse();
}

QJsonObject UserStateModel::getStat(ENUM::StatType type)
{
    QJsonObject result = {
        {"type", type},
    };

    transport->sendRequest(ENUM::GET_STAT, &result);

    return transport->readResponse();
}

void UserStateModel::onDisconnected()
{
    userData = {};
}
