#include "Model/TaskModel.hpp"

void TaskModel::reg(taskData &task, Model::UserModel::userData *data)
{
    if (data == nullptr) {
        return;
    }

//    QSqlDatabase connection = SharedObjects::getPointer()->getDatabase();

//    QSqlQuery query(connection);
//    query.prepare(
//        "INSERT INTO User("
//            "`owner`, `type`, `data`, `solution`, `add_stamp`"
//        ") VALUES("
//            ":owner, :type, :data, :solution, :add_stamp"
//        ")"
//    );
//    query.bindValue(":owner", data->id);
//    query.bindValue(":type", task.type);
//    query.bindValue(":data", task.data.c_str());
//    query.bindValue(":solution", task.solution.c_str());
//    query.bindValue(":add_stamp", QDateTime::currentSecsSinceEpoch());
//    query.exec();

//    task.id = query.lastInsertId().toInt();

    task.id  = 0;
}

bool TaskModel::isExists(taskData &task)
{
    return true;
}

bool TaskModel::isOwnedBy(taskData &task, Model::UserModel::userData *data)
{
    return true;
}
