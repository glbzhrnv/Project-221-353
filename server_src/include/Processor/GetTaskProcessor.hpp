#ifndef GETTASKPROCESSOR_HPP
#define GETTASKPROCESSOR_HPP

#include <stdint.h>
#include "Enum/RequestMethod.hpp"
#include "Processor/AbstractProcessor.hpp"

class GetTaskProcessor: public AbstractProcessor
{
public:
    /**
     * @brief Идентификатор метода
     */
    inline static const int32_t METHOD_ID = ENUM::GET_TASK;
    /**
     * @ingroup processor_response_code
     * @brief Коды состояния процессора CreateUserProcessor
     */
    enum ResponseCode: int32_t
    {
        SUCCESS = 0, //< Пользователь успешно создан
        INVALID_TYPE = 1, //< Не верный тип задания
        MUST_BE_LOGGED_ID = 2, //< Пользователь должен быть авторизован
        ALREADY_DONE = 3, //Задание уже выполнено
    };

    GetTaskProcessor();

    /**
     * @brief Производит обработку пользовательского запроса
     * @param params Параметры запроса
     * @param client Указатель на объект клиента
     */
    QByteArray process(QJsonObject params, ClientCore *client) override;
};

#endif // GETTASKPROCESSOR_HPP
