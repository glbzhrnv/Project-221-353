/**
 * @file
 * @brief Исключение вызванное ошибкой соединения
 */
#ifndef CONNECTIONEXCEPTION_HPP
#define CONNECTIONEXCEPTION_HPP

#include "AbstractRuntimeException.hpp"

/**
 * @ingroup exception
 * @brief Исключение вызванное ошибкой соединения
 */
class ConnectionException: public AbstractRuntimeException
{
public:
    explicit ConnectionException( const std::string& what_arg ): AbstractRuntimeException(what_arg)
    {
    }
};

#endif // CONNECTIONEXCEPTION_HPP
