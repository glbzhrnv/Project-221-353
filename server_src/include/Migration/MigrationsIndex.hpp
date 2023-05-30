#ifndef MIGRATIONSINDEX_H
#define MIGRATIONSINDEX_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "Migration/AbstractMigration.hpp"
#include "Migration/UserMigration.hpp"

class MigrationsIndex
{
public:
    static void setup(QSqlDatabase connection)
    {
        AbstractMigration *list[] = {
            new UserMigration(),
        };

        QSqlError error;
        for (AbstractMigration *ptr: list) {
            ptr->startMigration(connection);
            delete ptr;

            error = connection.lastError();
            if (error.isValid()) {
                qDebug() << error.text();
            }
        }
    }
};

#endif // MIGRATIONSINDEX_H
