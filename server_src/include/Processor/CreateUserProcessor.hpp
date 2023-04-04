/**
 * @file
 * @brief Обработчик запроса на регистрацию
 */
#ifndef CREATEUSERPROCESSOR_HPP
#define CREATEUSERPROCESSOR_HPP

#include <QJsonValue>
#include "AbstractProcessor.hpp"
#include "../ClientCore.hpp"

/**
 * @ingroup processor
 * @brief Обработчик запроса на авторизацию
 *
 * Позволяет пользователю создать в системе аккаунт
 */
class CreateUserProcessor: public AbstractProcessor
{
public:
    /**
     * @brief Идентификатор метода
     */
    inline static const int AUTH_METHOD = 1;

    /**
     * @brief Производит обработку пользовательского запроса
     * @param params Параметры запроса
     * @param client Указатель на объект клиента
     */
    static void process(QJsonValue params, ClientCore* client);
};

#endif // CREATEUSERPROCESSOR_HPP
