#ifndef SENDTASKPROCESSOR_H
#define SENDTASKPROCESSOR_H

#include <stdint.h>
#include "Enum/RequestMethod.hpp"
#include "Processor/AbstractProcessor.hpp"

class SendTaskProcessor: public AbstractProcessor
{
public:
    /**
     * @brief Идентификатор метода
     */
    inline static const int32_t METHOD_ID = ENUM::SEND_TASK;
    /**
     * @ingroup processor_response_code
     * @brief Коды состояния процессора CreateUserProcessor
     */
    enum ResponseCode: int32_t
    {
        SUCCESS = 0, //< Ответ на задание верен
        INVALID_TASK = 1, //< Не существующее задание
        INVALID_ANSWER = 2, //< Не верный ответ
    };

    SendTaskProcessor();

    /**
     * @brief Производит обработку ответа на задание
     * @param params Параметры запроса
     * @param client Указатель на объект клиента
     */
    QByteArray process(QJsonObject params, ClientCore *client) override;
};

#endif // SENDTASKPROCESSOR_H
