#ifndef REQUESTMETHOD_HPP
#define REQUESTMETHOD_HPP

#include <stdint.h>

namespace ENUM {

/**
 * @brief Идентификаторы возможных запросов к серверу
 */
enum RequestMethod: int32_t
{
    REG = 1,
    LOGIN = 2,
    LOGOUT = 3,
    GET_TASK = 4,
    SEND_TASK = 5,
    GET_STAT = 6,
};

}

#endif // REQUESTMETHOD_HPP
