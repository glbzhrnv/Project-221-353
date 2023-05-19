#include <QSqlQuery>
#include "Model/UserModel.hpp"
#include "Tools/PasswordTools.hpp"
#include "SharedObjects.hpp"

bool Model::UserModel::isExists(std::string login)
{
    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    QSqlQuery query(connection);
    query.prepare("SELECT COUNT(`login`) as 'cnt' FROM `User` WHERE `login` = :login");
    query.bindValue(":login", login.c_str());
    query.exec();
    query.first();

    return query.value("cnt").toInt() > 0;
}

void Model::UserModel::create(std::string login, std::string password)
{
    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    std::string hash = PasswordTools::passwordHash(password);

    QSqlQuery query(connection);
    query.prepare("INSERT INTO User(`login`, `password`) VALUES(:login, :password)");
    query.bindValue(":login", login.c_str());
    query.bindValue(":password", hash.c_str());
    query.exec();
}
