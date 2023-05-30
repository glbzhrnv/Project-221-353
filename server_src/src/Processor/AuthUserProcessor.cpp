#include "Model/UserModel.hpp"
#include "Model/UserStateModel.hpp"
#include "Processor/AuthUserProcessor.hpp"
#include "Tools/PasswordTools.hpp"

AuthUserProcessor::AuthUserProcessor()
{
    loginRegex = new std::regex(Model::UserModel::LOGIN_REGEX);
    passwordRegex = new std::regex(Model::UserModel::PASSWORD_REGEX);
}

AuthUserProcessor::~AuthUserProcessor()
{
    delete loginRegex;
    delete passwordRegex;
}

QByteArray AuthUserProcessor::process(QJsonObject params, ClientCore *client)
{
    Model::UserStateModel *userState = client->userStateGet();

    if (userState->authStatusGet() != ENUM::NO_AUTH) {
        return createResponse(ResponseCode::INVALID_PASSWORD);
    }

    std::string login = params["login"].toString().toStdString();
    if (!std::regex_match(login, *loginRegex)) {
        return createResponse(ResponseCode::INVALID_LOGIN);
    }

    std::string password = params["password"].toString().toStdString();
    if (!std::regex_match(password, *passwordRegex)) {
        return createResponse(ResponseCode::INVALID_PASSWORD);
    }

    Model::UserModel::userData data;
    if (!Model::UserModel::extract(login, data)) {
        return createResponse(ResponseCode::INVALID_PASSWORD);
    }

    if (!PasswordTools::passwordVerify(password, data.password)) {
        return createResponse(ResponseCode::INVALID_PASSWORD);
    }

    userState->tokenCreate();
    userState->dataSet(data);

    QJsonObject response = {
        {"login", data.login.c_str()},
        {"password", data.password.c_str()},
        {"is_teacher", data.is_teacher},
        {"token", userState->tokenGet().c_str()}
    };

    return createResponse(ResponseCode::SUCCESS, &response);
}
