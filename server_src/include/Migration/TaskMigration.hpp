#ifndef TASKMIGRATION_HPP
#define TASKMIGRATION_HPP

#include <QSqlQuery>
#include "AbstractMigration.hpp"

class UserMigration: public AbstractMigration
{
public:
    void startMigration(QSqlDatabase connection)
    {
        QSqlQuery query(connection);
        query.exec(
            "CREATE TABLE IF NOT EXISTS Task("
                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "owner INTEGER NOT NULL,"
                "type INTEGER NOT NULL,"
                "data TEXT NOT NULL,"
                "solution TEXT NOT NULL UNIQUE,"
                "add_stamp INTEGER NOT NULL"
            ")"
        );
    }
};

#endif // TASKMIGRATION_HPP
