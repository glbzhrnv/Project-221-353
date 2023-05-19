#ifndef USERMODEL_HPP
#define USERMODEL_HPP

#include <string>

namespace Model {
    class UserModel
    {
public:
        inline static const std::string LOGIN_REGEX = "^\\w{3,20}$";
        inline static const std::string PASSWORD_REGEX = "^\\w{8,64}$";

        static bool isExists(std::string login);

        static void create(std::string login, std::string password);
    };
}

#endif // USERMODEL_HPP
