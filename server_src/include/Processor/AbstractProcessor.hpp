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
public:
    inline static const std::string LOGIN_REGEX = "^\\w{3,20}$";
    inline static const std::string PASSWORD_REGEX = "^\\w{8,64}$";
protected:
    static QByteArray createResponse(int32_t code, QJsonObject* response = nullptr);
};

#endif // ABSTRACTPROCESSOR_HPP
