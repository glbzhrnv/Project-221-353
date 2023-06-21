/**
 * @defgroup processor Обработчики запросов
 * @brief Список всех доступных обработчиков запросов
 */

/**
 * @defgroup processor_response_code
 * @brief Коды возврата различных процессоров
 */

/**
 * @file
 * @brief Абстрактный обработчик запросов
 */
#ifndef ABSTRACTPROCESSOR_HPP
#define ABSTRACTPROCESSOR_HPP

#include <string>
#include <QJsonObject>
#include <QByteArray>
#include "ClientCore.hpp"

/**
 * @ingroup processor
 * @brief Абстрактный обработчик запросов
 *
 * Все обработчики должны расширять именно этот класс
 */
class AbstractProcessor
{
public:
    AbstractProcessor();

    virtual ~AbstractProcessor();

    /**
     * @brief Производит обработку пользовательского запроса
     * @param params Параметры запроса
     * @param client Указатель на объект клиента
     */
    virtual QByteArray process(QJsonObject params, ClientCore *client);

    static QByteArray createResponse(
        int32_t code,
        QJsonObject *response = nullptr,
        std::string text = ""
    );
};

#endif // ABSTRACTPROCESSOR_HPP
