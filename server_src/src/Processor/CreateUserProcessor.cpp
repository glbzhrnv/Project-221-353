#include <QRegularExpression>
#include <QSqlQuery>
#include <argon2.h>
#include "Processor/CreateUserProcessor.hpp"
#include "SharedObjects.hpp"

QByteArray CreateUser::Processor::process(QJsonObject params, ClientCore* client)
{
    if (client->getUserStatus() != UserStatus::NO_AUTH) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::ALREADY_LOGGED_IN);
    }

    QRegularExpression loginRE("^\\w{3,20}$");
    QRegularExpression passwordRE("^\\w{8,64}$");
    QString
        login = params["login"].toString(),
        password = params["password"].toString();

    if (!(loginRE.match(login).hasMatch() || passwordRE.match(password).hasMatch())) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::INVALID_PASSWORD);
    }

    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    QSqlQuery query(connection);
    query.prepare("INSERT INTO User(`login`, )");

    return "\nCreating user\n";
}
