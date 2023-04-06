#ifndef ABSTRACTMIGRATION_HPP
#define ABSTRACTMIGRATION_HPP

#include <QSqlDatabase>

class AbstractMigration
{
public:
    static void startMigration();
};

#endif // ABSTRACTMIGRATION_HPP
