#ifndef USERMODEL_HPP
#define USERMODEL_HPP

#include <string>

namespace Model {

class UserModel
{
public:
    inline static const std::string LOGIN_REGEX = "^\\w{3,20}$";
    inline static const std::string PASSWORD_REGEX = "^\\w{8,64}$";

    struct userData {
        int32_t id;
        std::string login;
        std::string password;
        bool is_teacher;
    };

    static bool isExists(std::string login);

    static Model::UserModel::userData create(std::string login, std::string password);

    static bool extract(std::string login, userData &data);
};

}

#endif // USERMODEL_HPP
