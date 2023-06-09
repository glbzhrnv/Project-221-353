#ifndef GETSTATPROCESSOR_HPP
#define GETSTATPROCESSOR_HPP

#include <stdint.h>
#include "Enum/RequestMethod.hpp"
#include "Processor/AbstractProcessor.hpp"

class GetStatProcessor: public AbstractProcessor
{
public:
    /**
     * @brief Идентификатор метода
     */
    inline static const int32_t METHOD_ID = ENUM::GET_STAT;
    /**
     * @ingroup processor_response_code
     * @brief Коды состояния процессора CreateUserProcessor
     */
    enum ResponseCode: int32_t
    {
        SUCCESS = 0, //< Пользователь успешно создан
        INVALID_TYPE = 1, //< Не верный тип задания
        MUST_BE_LOGGED_ID = 2, //< Пользователь должен быть авторизован
        MUST_BE_TEACHER = 3, //< Пользователь должен быть преподавателем, что бы получить данные
    };

    enum RequestCode: int32_t
    {
        USER_COUNT = 0, //< Колличество правильно и не правильно выполненных заданий
        TEACHER_DATA = 1, //< Данные об о всех учениках
    };

    GetStatProcessor();

    /**
     * @brief Производит обработку пользовательского запроса
     * @param params Параметры запроса
     * @param client Указатель на объект клиента
     */
    QByteArray process(QJsonObject params, ClientCore *client) override;
};

#endif // GETSTATPROCESSOR_HPP
