#include <QRegularExpression>
#include "../../include/Processor/CreateUserProcessor.hpp"

QByteArray CreateUser::Processor::process(QJsonObject params, ClientCore* client)
{
    if (client->getUserStatus() != UserStatus::NO_AUTH) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::ALREADY_LOGGED_IN);
    }

    QRegularExpression loginRE("^\w{3,15}$");
    QRegularExpression passwordRE("^\w{8,64}$");
    QString
        login = params["login"].toUtf8(),
        password = params["password"].toUtf8();

    if (!(loginRE.match(login).hasMatch() || passwordRE.match(password).hasMatch())) {
        return CreateUser::Processor::createResponse(CreateUser::ResponseCode::INVALID_PASSWORD);
    }

    return "\nCreating user\n";
}
