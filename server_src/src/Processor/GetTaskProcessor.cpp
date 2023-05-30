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

    if (type != ENUM::FSMTypeEnum::MEALY && type != ENUM::FSMTypeEnum::MOORE) {
        return createResponse(ResponseCode::INVALID_TYPE);
    }

    taskData task = TaskTools::taskCreate(type);
    TaskModel::reg(task, userState->dataGet());

    QJsonObject response = {
        {"task_id", task.id},
        {"data", task.data.c_str()},
    };

    return createResponse(ResponseCode::SUCCESS, &response);
}
