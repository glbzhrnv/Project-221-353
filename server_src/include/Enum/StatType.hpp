#ifndef STATTYPE_HPP
#define STATTYPE_HPP

#include <stdint.h>

namespace ENUM
{

/**
 * @brief Варинты выводимой статистики
 */
enum StatType: int32_t
{
    USER = 0, //< Запрос статистики для одного пользователя
    TEACHER = 1,  //< Запрос статистики о всех учениках
};

}

#endif // STATTYPE_HPP
