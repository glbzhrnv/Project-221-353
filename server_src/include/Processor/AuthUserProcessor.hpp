/**
 * @file
 * @brief Обработчик запроса на авторизацию
 */
#ifndef AUTHUSERPROCESSOR_HPP
#define AUTHUSERPROCESSOR_HPP

#include <QJsonObject>
#include "AbstractProcessor.hpp"
#include "../ClientCore.hpp"

namespace AuthUser
{
    /**
     * @brief Идентификатор метода
     */
    inline static const int METHOD_ID = 0;

    /**
     * @ingroup processor_response_code
     * @brief Коды состояния процессора CreateUserProcessor
     */
    enum ResponseCode: int
    {
        SUCCESS = 0, //< Авторизация успешна
        INVALID_PASSWORD = 1, //< Не верный логин или пароль
    };

    /**
     * @ingroup processor
     * @brief Обработчик запроса на авторизацию
     *
     * Позволяет пользователю авторизоваться в системе
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

#endif // AUTHUSERPROCESSOR_HPP