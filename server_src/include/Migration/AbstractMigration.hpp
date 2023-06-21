#ifndef ABSTRACTMIGRATION_HPP
#define ABSTRACTMIGRATION_HPP

#include <QSqlDatabase>

/**
 * @brief Абстрактный класс для миграции
 */
class AbstractMigration
{
public:
    virtual ~AbstractMigration();
    virtual void startMigration(QSqlDatabase connection) = 0;
};

#endif // ABSTRACTMIGRATION_HPP
