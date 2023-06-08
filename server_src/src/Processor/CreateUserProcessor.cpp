#include "Enum/UserAuthStateEnum.hpp"
#include "Model/UserModel.hpp"
#include "Model/UserStateModel.hpp"
#include "Processor/CreateUserProcessor.hpp"

CreateUserProcessor::CreateUserProcessor()
{
    loginRegex = new std::regex(Model::UserModel::LOGIN_REGEX);
    passwordRegex = new std::regex(Model::UserModel::PASSWORD_REGEX);
}

CreateUserProcessor::~CreateUserProcessor()
{
    delete loginRegex;
    delete passwordRegex;
}

QByteArray CreateUserProcessor::process(QJsonObject params, ClientCore *client)
{
    Model::UserStateModel *userState = client->userStateGet();

    if (userState->authStatusGet() != ENUM::NO_AUTH) {
        return createResponse(ResponseCode::ALREADY_LOGGED_IN);
    }

    std::string login = params["login"].toString().toStdString();
    if (!std::regex_match(login, *loginRegex)) {
        return createResponse(ResponseCode::INVALID_LOGIN);
    }

    std::string password = params["password"].toString().toStdString();
    if (!std::regex_match(password, *passwordRegex)) {
        return createResponse(ResponseCode::INVALID_PASSWORD);
    }

    if (Model::UserModel::isExists(login)) {
        return createResponse(ResponseCode::LOGIN_ALREADY_TAKEN);
    }

    Model::UserModel::userData data = Model::UserModel::create(login, password);

    userState->tokenCreate();
    userState->dataSet(data);
    userState->authStatusSet(ENUM::LOGGED_IN);

    QJsonObject response = {
        {"login", data.login.c_str()},
        {"password", data.password.c_str()},
        {"is_teacher", data.is_teacher},
        {"token", userState->tokenGet().c_str()}
    };

    return createResponse(ResponseCode::SUCCESS, &response);
}
