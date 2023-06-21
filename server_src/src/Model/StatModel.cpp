#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <string>
#include "Model/StatModel.hpp"
#include "Model/TaskModel.hpp"
#include "Model/UserModel.hpp"
#include "SharedObjects.hpp"

void StatModel::add(
    taskData &task,
    Model::UserModel::userData *user,
    std::string answer,
    bool isCorrect
) {
    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    QSqlQuery query(connection);
    query.prepare(
        "INSERT INTO Stat("
            "`owner_id`, `task_id`, `answer`, `is_correct`, `add_stamp`"
        ") VALUES("
            ":owner_id, :task_id, :answer, :is_correct, :add_stamp"
        ")"
    );
    query.bindValue(":owner_id", user->id);
    query.bindValue(":task_id", task.id);
    query.bindValue(":answer", answer.c_str());
    query.bindValue(":is_correct", isCorrect);
    query.bindValue(":add_stamp", QDateTime::currentSecsSinceEpoch());
    query.exec();

    qDebug() << "dbid: " << task.id << query.lastError().databaseText();
}

int32_t StatModel::getCount(Model::UserModel::userData *user, bool correct)
{
    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    QSqlQuery query(connection);
    query.prepare(
        "SELECT "
            "COUNT(`id`) as 'cnt' "
        "FROM `Stat` "
        "WHERE `is_correct` = :is_correct AND owner_id = :owner_id"
    );
    query.bindValue(":is_correct", correct);
    query.bindValue(":owner_id", user->id);
    query.exec();

    if (!(query.isActive() && query.first())) {
        return 0;
    }

    return query.value("cnt").toInt();
}

QJsonObject StatModel::getData(int32_t limit, int32_t offset)
{
    QJsonObject data;

    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

    QSqlQuery query(connection);
    query.prepare(
        "SELECT"
            "`id`, `login`"
        "FROM `User` "
        "LIMIT :limit "
        "OFFSET :offset"
    );
    query.bindValue(":limit", limit);
    query.bindValue(":offset", offset);
    query.exec();

    if (!query.isActive()) {
        return data;
    }

    while(query.next()) {
        QString ownerId = query.value("id").toString();

        QJsonObject row = {
            {"id", ownerId},
            {"login", query.value("login").toString()},
        };

        QJsonObject results = {};
        for (int32_t i = 0; i < 5; i++) {

            taskResult task;
            int32_t j = TaskModel::isSolved(ownerId.toInt(), i, task);

            qDebug() << "------ Task is solved " << j;
            if (j != 2) {
                continue;
            }

            QJsonObject answer = {
                {"id", task.id},
                {"type", task.type},
                {"answer", task.answer.c_str()},
                {"is_correct", task.is_correct},
            };
            results[std::to_string(i).c_str()] = answer;
        }
        row["results"] = results;

        data[ownerId] = row;
    }

    return data;
}
