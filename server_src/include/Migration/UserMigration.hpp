#ifndef USERMIGRATION_HPP
#define USERMIGRATION_HPP

#include <QSqlQuery>
#include "AbstractMigration.hpp"

/**
 * @brief Миграция, создающая таблицу с учётными данными пользователей
 */
class UserMigration: public AbstractMigration
{
public:
    void startMigration(QSqlDatabase connection)
    {
        QSqlQuery query(connection);
        query.exec(
            "CREATE TABLE IF NOT EXISTS User("
                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "login VARCHAR(20) NOT NULL UNIQUE,"
                "password VARCHAR(100) NOT NULL,"
                "is_teacher TINYINT(1) NOT NULL DEFAULT(0)"
            ")"
        );
    }
};

#endif // USERMIGRATION_HPP
