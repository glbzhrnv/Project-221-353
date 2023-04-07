#ifndef PASSWORDTOOLS_HPP
#define PASSWORDTOOLS_HPP

#include <cstdint>
#include <string>

class PasswordTools
{
public:
    inline static constexpr uint32_t
        hash_len = 32,
        salt_len = 16,
        m_cost = (1<<16),
        t_cost = 4,
        parallelism = 2;

    static std::string passwordHash(std::string password);

    static bool passwordVerify(std::string passsword, std::string hash);
};

#endif // PASSWORDTOOLS_HPP
