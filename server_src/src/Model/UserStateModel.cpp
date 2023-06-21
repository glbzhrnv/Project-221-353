#include "Model/UserStateModel.hpp"
#include "Model/UserModel.hpp"

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
