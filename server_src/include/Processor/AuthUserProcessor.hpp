/**
 * @file
 * @brief Обработчик запроса на авторизацию
 */
#ifndef AUTHUSERPROCESSOR_HPP
#define AUTHUSERPROCESSOR_HPP

#include <QJsonValue>
#include "AbstractProcessor.hpp"
#include "../ClientCore.hpp"

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
    inline static const int AUTH_METHOD = 0;

    /**
     * @brief Производит обработку пользовательского запроса
     * @param params Параметры запроса
     * @param client Указатель на объект клиента
     */
    static void process(QJsonValue params, ClientCore* client);
};

#endif // AUTHUSERPROCESSOR_HPP
