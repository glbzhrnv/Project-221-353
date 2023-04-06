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

#include <QJsonObject>

/**
 * @ingroup processor
 * @brief Абстрактный обработчик запросов
 *
 * Все обработчики должны расширять именно этот класс
 */
class AbstractProcessor
{
protected:
    static QByteArray createResponse(int code, QJsonObject* response = nullptr);
};

#endif // ABSTRACTPROCESSOR_HPP
