#ifndef USERSTATEMODEL_HPP
#define USERSTATEMODEL_HPP

#include <string>
#include "Enum/UserAuthStateEnum.hpp"
#include "Model/UserModel.hpp"

namespace Model {

class UserStateModel
{
public:
    void tokenSet(std::string);

    std::string tokenGet();

    bool isTokenExists();

    void authStatusSet(ENUM::UserAuthStateEnum value);

    std::string tokenCreate();

    bool tokenCheck(std::string token);

    ENUM::UserAuthStateEnum authStatusGet();

    void dataSet(Model::UserModel::userData value);

    Model::UserModel::userData* dataGet();

protected:
    /**
     * Текущий статус пользователя
     */
    ENUM::UserAuthStateEnum authStatus = ENUM::NO_AUTH;

    std::string token = "";

    Model::UserModel::userData userData = {};
};

}

#endif // USERSTATEMODEL_HPP
