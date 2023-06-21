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

/**
 * @brief Хранит все данные связанные с пользователем
 */
class UserStateModel: public QObject
{
    Q_OBJECT

public:
    UserStateModel(QObject* parent = nullptr);

    ~UserStateModel();

    /**
     * @brief Устанавливает на соединение необходиме события
     * @param transport Объект соединения
     */
    void setTransport(Transport* transport);

    /**
     * @brief Проверяет, авторизован ли пользователь в данный момент
     * @return
     */
    bool isLoggedIn();

    /**
     * @brief Производит регистрацию пользователя на сервере
     * @param login - Логин
     * @param password - Пароль
     * @return Результат запроса
     */
    QJsonObject reg(std::string login, std::string password);

    /**
     * @brief Производит авторизацию пользователя на сервере
     * @param login - Логин
     * @param password - Пароль
     * @return Результат запроса
     */
    QJsonObject login(std::string login, std::string password);

    /**
     * @brief Производит выход пользователя из аккаунта
     * @return
     */
    bool logout();

    /**
     * @brief Получет задание с сервера
     * @param type - Тип задания
     * @return Данные задания
     */
    QJsonObject getTask(ENUM::FSMType type);

    /**
     * @brief Отправляет результат выполнения задания на сервер
     * @param taskId - Идентификатор задания
     * @param answer - Ответ на задание
     * @return Результат проверки
     */
    QJsonObject sendTask(int32_t taskId, QString answer);

    /**
     * @brief Запрашивает статистику с сервера
     * @param type - Тип статистики
     * @return - Данные статистики
     */
    QJsonObject getStat(ENUM::StatType type);

public slots:
    /**
     * @brief Реалирование на закрытие соденения с сервером
     */
    void onDisconnected();

signals:
    /**
     * @brief Событие на случай авторизации пользователя
     */
    void loggedIn(QJsonObject*);

    /**
     * @brief Событие на случай выхода пользователя из аккаунта
     */
    void loggedOut(QJsonObject*);

    /**
     * @brief Событие на случай регистрации
     */
    void registered(QJsonObject*);

    /**
     * @brief Событие на случай выполнения, пользователем, задания
     */
    void taskComplete();

protected:
    /**
     * @brief state Текущее состоянеие авторизации
     * 0 - не авторизован
     * 1 - авторизован
     */
    uint32_t state = 0;

    /**
     * @brief Данные пользователя
     */
    struct userDataStruct {
        std::string username;
        bool is_teacher;
    } userData = {};

    Transport* transport;
};

#endif // USERSTATEMODEL_HPP
