#include <QSqlDatabase>
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

    if (!query.isActive()) {
        return false;
    }

    query.first();

    return query.value("cnt").toInt() > 0;
}

Model::UserModel::userData Model::UserModel::create(std::string login, std::string password)
{
    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    std::string hash = PasswordTools::passwordHash(password);

    QSqlQuery query(connection);
    query.prepare("INSERT INTO User(`login`, `password`) VALUES(:login, :password)");
    query.bindValue(":login", login.c_str());
    query.bindValue(":password", hash.c_str());
    query.exec();

    return {
        .id = query.lastInsertId().toInt(),
        .login = login,
        .password = hash,
        .is_teacher = false
    };
}

bool Model::UserModel::extract(std::string login, userData &data)
{
    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    QSqlQuery query(connection);
    query.prepare("SELECT `id`, `login`, `password`, `is_teacher` FROM `User` WHERE `login` = :login");
    query.bindValue(":login", login.c_str());
    query.exec();

    if (!query.isActive()) {
        return false;
    }

    query.first();

    data = {
        .id = query.value("id").toInt(),
        .login = query.value("login").toString().toStdString(),
        .password = query.value("password").toString().toStdString(),
        .is_teacher = query.value("is_teacher").toBool()
    };

    return true;
}
