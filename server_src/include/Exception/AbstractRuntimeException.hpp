/**
 * @defgroup exception Исключения
 * @brief Список всех доступных исключений
 */

/**
 * @file
 * @brief Абстрактное исклюение времени исполнения
 */
#ifndef ABSTRACTRUNTIMEEXCEPTION_H
#define ABSTRACTRUNTIMEEXCEPTION_H

#include <stdexcept>

/**
 * @brief Абстрактное исклюение времени исполнения
 */
class AbstractRuntimeException: std::runtime_error
{
public:
    explicit AbstractRuntimeException( const std::string& what_arg ): runtime_error(what_arg)
    {
    }
};

#endif // ABSTRACTRUNTIMEEXCEPTION_H
