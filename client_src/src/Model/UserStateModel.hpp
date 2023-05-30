#ifndef USERSTATEMODEL_HPP
#define USERSTATEMODEL_HPP

#include <string>
#include <memory>
#include <QObject>
#include <QJsonObject>
#include <QTcpSocket>
#include "Enum/FSMType.hpp"
#include "Enum/StatType.hpp"
#include "Transport.hpp"

class UserStateModel: public QObject
{
    Q_OBJECT

public:
    UserStateModel(QObject* parent = nullptr);

    ~UserStateModel();

    void setSocket(QTcpSocket* socket);

    bool isLoggedIn();

    QJsonObject reg(std::string login, std::string password);

    QJsonObject login(std::string login, std::string password);

    bool logout();

    QJsonObject getTask(ENUM::FSMType type);

    QJsonObject sendTask(int32_t taskId, QString answer);

    QJsonObject getStat(ENUM::StatType type);

public slots:
    void onDisconnected();

signals:
    void loggedIn(QJsonObject*);

    void loggedOut(QJsonObject*);

    void registered(QJsonObject*);

    void taskComplete();

protected:
    /**
     * @brief state Текущее состоянеие авторизации
     * 0 - не авторизован
     * 1 - авторизован
     */
    uint32_t state = 0;

    struct userDataStruct {
        std::string username;
        bool is_teacher;
    } userData = {};

    Transport* socket;
};

#endif // USERSTATEMODEL_HPP
