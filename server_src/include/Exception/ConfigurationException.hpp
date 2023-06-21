/**
 * @file
 * @brief Исключение вызванное ошибкой конфигурации
 */
#ifndef CONFIGURATIONEXCEPTION_HPP
#define CONFIGURATIONEXCEPTION_HPP

#include "AbstractRuntimeException.hpp"

/**
 * @ingroup exception
 * @brief Исключение вызванное ошибкой конфигурации
 */
class ConfigurationException: public AbstractRuntimeException
{
public:
    explicit ConfigurationException( const std::string& what_arg ): AbstractRuntimeException(what_arg)
    {
    }
};

#endif // CONFIGURATIONEXCEPTION_HPP
