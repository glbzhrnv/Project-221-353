#include "Tools/PasswordTools.hpp"
#include <cstdint>
#include <random>
#include <stdlib.h>
#include <argon2.h>
#include <string.h>

uint8_t* PasswordTools::genSalt(uint32_t size)
{
    uint8_t *result = (uint8_t*)malloc(size);

    for(uint32_t i = 0; i < size; i++) {
        result[i] = (uint8_t)rand();
    }

    return result;
}

std::string PasswordTools::passwordHash(std::string password)
{
    size_t encoded_len = argon2_encodedlen(
        t_cost, m_cost,
        parallelism,
        salt_len, hash_len,
        Argon2_type::Argon2_id
    );
    char *encoded = (char*)malloc(encoded_len);

    uint8_t *salt = PasswordTools::genSalt(salt_len);
    argon2id_hash_encoded(
        t_cost, m_cost,
        parallelism,
        password.c_str(), password.size(),
        salt, salt_len,
        hash_len,
        encoded, encoded_len
    );

    std::string result(encoded, encoded_len);
    free(encoded);
    free(salt);

    return result;
//    return password;
}


bool PasswordTools::passwordVerify(std::string password, std::string hash)
{
    return argon2id_verify(
        hash.c_str(),
        password.c_str(),
        password.size()
    ) == ARGON2_OK;

//    return password == hash;
}
