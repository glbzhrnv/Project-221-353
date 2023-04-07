#include "Tools/PasswordTools.hpp"
#include <argon2.h>
#include <random>

std::string PasswordTools::passwordHash(std::string password)
{
    const char* pwd = password.c_str();
    char salt = random();

    size_t encoded_len = argon2_encodedlen(
        t_cost, m_cost,
        parallelism,
        salt_len, hash_len,
        Argon2_type::Argon2_id
    );

    char* encoded = new char(encoded_len);

    argon2id_hash_encoded(
        t_cost, m_cost,
        parallelism,
        pwd, password.size(),
        &salt, salt_len,
        hash_len,
        encoded, encoded_len
    );

    std::string str(encoded);
//    delete encoded;

    return str;
}


//bool PasswordTools::passwordVerify(std::string password, std::string hash)
//{
//    return false;
//}
