#include "Model/UserStateModel.hpp"
#include "Model/UserModel.hpp"

void Model::UserStateModel::tokenSet(std::string value)
{
    token = value;
}

std::string Model::UserStateModel::tokenGet()
{
    return token;
}

bool Model::UserStateModel::isTokenExists()
{
    return token == "";
}

std::string Model::UserStateModel::tokenCreate()
{
    std::string token = "asd";

    this->tokenSet(token);

    return token;
}

bool Model::UserStateModel::tokenCheck(std::string value)
{
    return token == value;
}

void Model::UserStateModel::authStatusSet(ENUM::UserAuthStateEnum value)
{
    authStatus = value;
}

ENUM::UserAuthStateEnum Model::UserStateModel::authStatusGet()
{
    return authStatus;
}

void Model::UserStateModel::dataSet(Model::UserModel::userData value)
{
    userData = value;
}

Model::UserModel::userData* Model::UserStateModel::dataGet()
{
    return &userData;
}
