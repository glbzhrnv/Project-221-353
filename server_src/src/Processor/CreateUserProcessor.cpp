#include <regex>
#include <argon2.h>
#include <iostream>
#include "Model/UserModel.hpp"
#include "Processor/CreateUserProcessor.hpp"

QByteArray CreateUser::Processor::process(QJsonObject params, ClientCore* client)
{
    if (client->getUserStatus() != UserStatus::NO_AUTH) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::ALREADY_LOGGED_IN);
    }

    std::string login = params["login"].toString().toStdString();
    std::regex loginRE(Model::UserModel::LOGIN_REGEX);
    if (!std::regex_match(login, loginRE)) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::INVALID_LOGIN);
    }

    std::string password = params["password"].toString().toStdString();
    std::regex passwordRE(Model::UserModel::PASSWORD_REGEX);
    if (!std::regex_match(password, passwordRE)) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::INVALID_PASSWORD);
    }

    if (Model::UserModel::isExists(login)) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::LOGIN_ALREADY_TAKEN);
    }

    Model::UserModel::create(login, password);

    return CreateUser::Processor::createResponse(CreateUser::ResponseCode::SUCCESS);
}
