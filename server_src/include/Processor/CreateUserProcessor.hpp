/**
 * @file
 * @brief Обработчик запроса на регистрацию
 */
#ifndef CREATEUSERPROCESSOR_HPP
#define CREATEUSERPROCESSOR_HPP

#include <QJsonObject>
#include <QSqlDatabase>
#include "AbstractProcessor.hpp"
#include "../ClientCore.hpp"

namespace CreateUser
{
    /**
     * @brief Идентификатор метода
     */
    inline static const int METHOD_ID = 1;
    /**
     * @ingroup processor_response_code
     * @brief Коды состояния процессора CreateUserProcessor
     */
    enum ResponseCode: int
    {
        SUCCESS = 0, //< Пользователь успешно создан
        ALREADY_LOGGED_IN = 1, //< Пользователь уже авторизован. Создание аккаунта невозможно
        INVALID_PASSWORD = 2, //< Не верный логин или пароль
        LOGIN_TAKEN = 3, //< Данный пользователь уже зарегистрирован
        WEAK_PASSWORD = 4, //< Пароль не отвечает требованиям безопасности
    };

    /**
     * @ingroup processor
     * @brief Обработчик запроса на авторизацию
     *
     * Позволяет пользователю создать в системе аккаунт
     */
    class Processor: public AbstractProcessor
    {
    public:
        /**
         * @brief Производит обработку пользовательского запроса
         * @param params Параметры запроса
         * @param client Указатель на объект клиента
         */
        static QByteArray process(QJsonObject params, ClientCore* client);
    };
}

#endif // CREATEUSERPROCESSOR_HPP
