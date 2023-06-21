#include <QDebug>
#include <QJsonObject>
#include "Enum/FSMTypeEnum.hpp"
#include "Enum/UserAuthStateEnum.hpp"
#include "Model/TaskModel.hpp"
#include "Processor/GetTaskProcessor.hpp"
#include "Tools/TaskTools.hpp"

GetTaskProcessor::GetTaskProcessor()
{
}

QByteArray GetTaskProcessor::process(QJsonObject params, ClientCore *client)
{
    Model::UserStateModel *userState = client->userStateGet();

    if (userState->authStatusGet() != ENUM::LOGGED_IN) {
        return createResponse(ResponseCode::MUST_BE_LOGGED_ID);
    }

    ENUM::FSMTypeEnum type = static_cast<ENUM::FSMTypeEnum>(
        params["type"].toInt()
    );

//    if (TaskModel::isDone(userState->dataGet()->id, type)) {
//        return createResponse(ResponseCode::ALREADY_DONE);
//    }

//    taskData task = {};
//    if (TaskModel::isRegistered(userState->dataGet()->id, type, task)) {

//    } else {
        taskData task = TaskTools::create(type);
        TaskModel::reg(task, userState->dataGet());

        qDebug() << "New task: " << task.id << " | Solution: " << task.solution.c_str();
//    }

    QJsonObject response = {
        {"id", task.id},
        {"type", task.type},
        {"data", task.data.c_str()},
    };

    return createResponse(ResponseCode::SUCCESS, &response);
}
