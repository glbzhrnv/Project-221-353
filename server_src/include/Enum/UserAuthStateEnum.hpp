#ifndef USERAUTHSTATEENUM_HPP
#define USERAUTHSTATEENUM_HPP

#include <stdint.h>

namespace ENUM
{

/**
 * @brief Варинты состояний пользователя
 */
enum UserAuthStateEnum: int32_t
{
    NO_AUTH = 0, //< Не авторизован
    LOGGED_IN = 1, //< Обычный пользователь
};

}

#endif // USERAUTHSTATEENUM_HPP
