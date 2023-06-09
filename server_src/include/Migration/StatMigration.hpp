#ifndef STATMIGRATION_HPP
#define STATMIGRATION_HPP

#include <QSqlQuery>
#include "AbstractMigration.hpp"

class StatMigration: public AbstractMigration
{
public:
    void startMigration(QSqlDatabase connection)
    {
        QSqlQuery query(connection);
        query.exec(
            "CREATE TABLE IF NOT EXISTS Stat("
                "id INTEGER NOT NULL,"
                "owner_id INTEGER NOT NULL,"
                "task_id INTEGER NOT NULL,"
                "answer TEXT NOT NULL,"
                "is_correct INTEGER NOT NULL,"
                "add_stamp INTEGER NOT NULL,"
                "FOREIGN KEY(task_id) REFERENCES Task(id),"
                "PRIMARY KEY(id AUTOINCREMENT),"
                "FOREIGN KEY(owner_id) REFERENCES User(id)"
            ")"
        );
    }
};

#endif // STATMIGRATION_HPP
