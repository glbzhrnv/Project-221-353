#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include "Enum/FSMTypeEnum.hpp"
#include "Model/TaskModel.hpp"
#include "SharedObjects.hpp"

void TaskModel::reg(taskData &task, Model::UserModel::userData *data)
{
    if (data == nullptr) {
        return;
    }

    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    QSqlQuery query(connection);
    query.prepare(
        "INSERT INTO Task("
            "`owner_id`, `type`, `data`, `solution`, `is_solved`, `add_stamp`"
        ") VALUES("
            ":owner_id, :type, :data, :solution, :is_solved, :add_stamp"
        ")"
    );
    query.bindValue(":owner_id", data->id);
    query.bindValue(":type", task.type);
    query.bindValue(":data", task.data.c_str());
    query.bindValue(":solution", task.solution.c_str());
    query.bindValue(":is_solved", task.is_solved);
    query.bindValue(":add_stamp", QDateTime::currentSecsSinceEpoch());
    query.exec();

    qDebug() << "dbid: " << task.id << query.lastError().databaseText();

    task.id = query.lastInsertId().toInt();
}

bool TaskModel::getData(int32_t id, int32_t owner, taskData &data)
{
    qDebug() << "Task id: " << id << " | Owner: " << owner;

    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    QSqlQuery query(connection);
    query.prepare(
        "SELECT"
            "`type`, `data`, `solution`, `is_solved`"
        "FROM `Task`"
        "WHERE `id` = :id AND `owner_id` = :owner_id"
    );
    query.bindValue(":id", id);
    query.bindValue(":owner_id", owner);
    query.exec();

    if (!(query.isActive() && query.first())) {
        return false;
    }

    data.id = id;
    data.type = (ENUM::FSMTypeEnum) query.value("type").toInt();
    data.data = query.value("data").toString().toStdString();
    data.solution = query.value("solution").toString().toStdString();
    data.is_solved = query.value("is_solved").toBool();

    qDebug() << "Task found";

    return true;
}

int32_t TaskModel::isRegistered(int32_t owner, int32_t type)
{
    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();
    QSqlQuery query(connection);

    query.prepare(
        "SELECT `id` "
        "FROM `Task` "
        "WHERE `owner_id` = :owner_id AND `type` = :type "
        "LIMIT 1"
    );
    query.bindValue(":owner_id", owner);
    query.bindValue(":type", type);
    query.exec();

    if (query.isActive() && query.first()) {
        return query.value("id").toInt();
    } else {
        return -1;
    }
}

int32_t TaskModel::isSolved(int32_t owner, int32_t type, taskResult &result)
{

    int32_t id = isRegistered(owner, type);

    qDebug() << "owner " << owner << " type " << type << " id " << id;
    if (id == -1) {
        return 0;
    }

    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();
    QSqlQuery query(connection);

    query.prepare(
        "SELECT "
            "`id`, `answer`, `is_correct` "
        "FROM `Stat` "
        "WHERE `owner_id` = :owner_id AND `task_id` = :task_id "
        "LIMIT 1"
    );
    query.bindValue(":owner_id", owner);
    query.bindValue(":task_id", id);
    query.exec();

    if (!(query.isActive() && query.first())) {
        return 1;
    }

    qDebug() << "-------------SOLVED " << id;

    result.id = query.value("id").toInt();
    result.type = type;
    result.answer = query.value("answer").toString().toStdString();
    result.is_correct = query.value("is_correct").toBool();

    return 2;
}

