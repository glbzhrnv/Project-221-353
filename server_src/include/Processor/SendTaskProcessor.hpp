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
        SUCCESS = 0, //< Пользователь успешно создан
        MUST_BE_LOGGED_ID = 2, //< Пользователь должен быть авторизован
    };

    SendTaskProcessor();

    /**
     * @brief Производит обработку пользовательского запроса
     * @param params Параметры запроса
     * @param client Указатель на объект клиента
     */
    QByteArray process(QJsonObject params, ClientCore *client) override;
};

#endif // SENDTASKPROCESSOR_H
