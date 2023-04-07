#ifndef ABSTRACTMIGRATION_HPP
#define ABSTRACTMIGRATION_HPP

#include <QSqlDatabase>

class AbstractMigration
{
public:
    virtual ~AbstractMigration();
    virtual void startMigration(QSqlDatabase connection) = 0;
};

#endif // ABSTRACTMIGRATION_HPP
