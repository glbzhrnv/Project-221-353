#include <QSqlQuery>
#include <regex>
#include <argon2.h>
#include <iostream>
#include "Processor/CreateUserProcessor.hpp"
#include "SharedObjects.hpp"
#include "Tools/PasswordTools.hpp"

bool CreateUser::Processor::isUserExists(std::string login)
{
    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    QSqlQuery query(connection);
    query.prepare("SELECT COUNT(`login`) as 'cnt' FROM `User` WHERE `login` = :login");
    query.bindValue(":login", login.c_str());
    query.exec();
    query.first();

    return query.value("cnt").toInt() > 0;
}

void CreateUser::Processor::Create(std::string login, std::string password)
{
    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    std::string hash = PasswordTools::passwordHash(password);

    QSqlQuery query(connection);
    query.prepare("INSERT INTO User(`login`, `password`) VALUES(:login, :password)");
    query.bindValue(":login", login.c_str());
    query.bindValue(":password", hash.c_str());
    query.exec();
}

QByteArray CreateUser::Processor::process(QJsonObject params, ClientCore* client)
{
    if (client->getUserStatus() != UserStatus::NO_AUTH) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::ALREADY_LOGGED_IN);
    }

    std::string login = params["login"].toString().toStdString();
    std::regex loginRE(CreateUser::Processor::LOGIN_REGEX);
    if (!std::regex_match(login, loginRE)) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::INVALID_LOGIN);
    }

    std::string password = params["password"].toString().toStdString();
    std::regex passwordRE(PASSWORD_REGEX);
    if (!std::regex_match(password, passwordRE)) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::INVALID_PASSWORD);
    }

    if (CreateUser::Processor::isUserExists(login)) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::LOGIN_ALREADY_TAKEN);
    }


    CreateUser::Processor::Create(login, password);

    return CreateUser::Processor::createResponse(CreateUser::ResponseCode::SUCCESS);
}
