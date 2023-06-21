#ifndef PASSWORDTOOLS_HPP
#define PASSWORDTOOLS_HPP

#include <cstdint>
#include <string>

/**
 * @brief Предоставляет все наобходимые функции для безопасной работы с паролями
 */
class PasswordTools
{
public:
    /**
     * @brief Параметры алгоритма хеширования
     */
    inline static constexpr uint32_t
        hash_len = 32,
        salt_len = 10,
        m_cost = (1<<16),
        t_cost = 4,
        parallelism = 2;

    /**
     * @brief Возвращает случайное число, необходимое для хеширования данных
     * @param size Размер соли
     * @return Соль
     */
    static uint8_t* genSalt(uint32_t size);

    /**
     * @brief Выполняет хеширвоание пароля
     * @param password Строка с паролем
     * @return Результат работы хеш-функции
     */
    static std::string passwordHash(std::string password);

    /**
     * @brief Сверяет пароль и хеш
     * @param passsword - Пароль
     * @param hash Хеш
     * @return Результат сверки
     */
    static bool passwordVerify(std::string passsword, std::string hash);
};

#endif // PASSWORDTOOLS_HPP
