/**
 * @file
 * @brief Обработчик запроса на авторизацию
 */
#ifndef AUTHUSERPROCESSOR_HPP
#define AUTHUSERPROCESSOR_HPP

#include <regex>
#include <QJsonObject>
#include "Enum/RequestMethod.hpp"
#include "Processor/AbstractProcessor.hpp"
#include "ClientCore.hpp"



/**
 * @ingroup processor
 * @brief Обработчик запроса на авторизацию
 *
 * Позволяет пользователю авторизоваться в системе
 */
class AuthUserProcessor: public AbstractProcessor
{
public:
    /**
    * @brief Идентификатор метода
    */
    inline static const int32_t METHOD_ID = ENUM::LOGIN;

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
    };

    AuthUserProcessor();

    ~AuthUserProcessor();

    /**
    * @brief Производит обработку пользовательского запроса
    * @param params Параметры запроса
    * @param client Указатель на объект клиента
    */
    QByteArray process(QJsonObject params, ClientCore *client) override;

protected:
    std::regex *loginRegex;
    std::regex *passwordRegex;
};

#endif // AUTHUSERPROCESSOR_HPP
