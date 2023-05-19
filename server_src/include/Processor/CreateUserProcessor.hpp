/**
 * @file
 * @brief Обработчик запроса на регистрацию
 */
#ifndef CREATEUSERPROCESSOR_HPP
#define CREATEUSERPROCESSOR_HPP

#include <QJsonObject>
#include <QSqlDatabase>
#include "Processor/AbstractProcessor.hpp"
#include "ClientCore.hpp"

namespace CreateUser
{
    /**
     * @brief Идентификатор метода
     */
    inline static const int32_t METHOD_ID = 2;
    /**
     * @ingroup processor_response_code
     * @brief Коды состояния процессора CreateUserProcessor
     */
    enum ResponseCode: int32_t
    {
        SUCCESS = 0, //< Пользователь успешно создан
        ALREADY_LOGGED_IN = 1, //< Пользователь уже авторизован. Создание аккаунта невозможно
        INVALID_LOGIN = 2, //< Логин не соответствует требованиям
        INVALID_PASSWORD = 3, //< Пароль не соответствует требованиям
        LOGIN_ALREADY_TAKEN = 4, //< Данный пользователь уже зарегистрирован
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
